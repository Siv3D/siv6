//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Error.hpp>
# include <Siv3D/Utility.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/UserAction.hpp>
# include <Siv3D/DLL.hpp>
# include <Siv3D/Profiler/IProfiler.hpp>
# include <Siv3D/UserAction/IUSerAction.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "CWindow.hpp"
# include "DPIAwareness.hpp"
# include "WindowProc.hpp"
# include <dwmapi.h>

namespace s3d
{
	namespace detail
	{
		static void RegisterWindowClass(HINSTANCE hInstance, const wchar_t* className)
		{
			LOG_SCOPED_TRACE(U"RegisterWindowClass()");

			const WNDCLASSEX windowClass
			{
				.cbSize			= sizeof(WNDCLASSEX),
				.style			= CS_HREDRAW | CS_VREDRAW,
				.lpfnWndProc	= WindowProc,
				.hInstance		= hInstance,
				.hIcon			= ::LoadIconW(hInstance, MAKEINTRESOURCEW(100)),
				.hCursor		= ::LoadCursorW(nullptr, IDC_ARROW),
				.hbrBackground	= static_cast<HBRUSH>(::GetStockObject(DKGRAY_BRUSH)),
				.lpszClassName	= className
			};

			LOG_VERBOSE(U"RegisterClassExW()");
			if (!::RegisterClassExW(&windowClass))
			{
				throw EngineError(U"RegisterClassExW() failed");
			}
		}

		void DisableTouchFeedbackVisualization(HWND hWND, HMODULE user32)
		{
			if (decltype(SetWindowFeedbackSetting) * pSetWindowFeedbackSetting = DLL::GetFunctionNoThrow(user32, "SetWindowFeedbackSetting"))
			{
				static constexpr std::array<FEEDBACK_TYPE, 11> feedbackTypes =
				{
					FEEDBACK_TOUCH_CONTACTVISUALIZATION,
					FEEDBACK_PEN_BARRELVISUALIZATION,
					FEEDBACK_PEN_TAP,
					FEEDBACK_PEN_DOUBLETAP,
					FEEDBACK_PEN_PRESSANDHOLD,
					FEEDBACK_PEN_RIGHTTAP,
					FEEDBACK_TOUCH_TAP,
					FEEDBACK_TOUCH_DOUBLETAP,
					FEEDBACK_TOUCH_PRESSANDHOLD,
					FEEDBACK_TOUCH_RIGHTTAP,
					FEEDBACK_GESTURE_PRESSANDTAP,
				};

				for (const auto& feedbackType : feedbackTypes)
				{
					BOOL val = FALSE;
					pSetWindowFeedbackSetting(hWND, feedbackType, 0, sizeof(BOOL), &val);
				}
			}
		}

		constexpr uint32 GetWindowStyleFlags(const WindowStyle style) noexcept
		{
			switch (style)
			{
			case WindowStyle::Fixed:
				return (WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME));
			case WindowStyle::Frameless:
				return (WS_POPUP | WS_VISIBLE | WS_MINIMIZEBOX);
			case WindowStyle::Sizable:
			default:
				return WS_OVERLAPPEDWINDOW;
			}
		}

		inline constexpr Rect ToRect(const RECT& rect) noexcept
		{
			return Rect(rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top));
		}
	}

	CWindow::CWindow()
	{

	}

	CWindow::~CWindow()
	{
		LOG_SCOPED_TRACE(U"CWindow::~CWindow()");

		if (m_hWnd)
		{
			LOG_VERBOSE(U"DestroyWindow()");
			::DestroyWindow(m_hWnd);
		}

		LOG_VERBOSE(U"UnregisterClassW()");
		::UnregisterClassW(m_windowClassName.c_str(), m_hInstance);

		if (m_user32)
		{
			::FreeLibrary(m_user32);
			m_user32 = nullptr;
		}
	}

	void CWindow::init()
	{
		LOG_SCOPED_TRACE(U"CWindow::init()");

		// user32.dll
		{
			m_user32 = DLL::LoadSystemLibrary(L"user32.dll");

			if (!m_user32)
			{
				throw EngineError(U"Failed to load `user32.dll`");
			}

			m_pGetSystemMetricsForDpi = DLL::GetFunctionNoThrow(m_user32, "GetSystemMetricsForDpi");
		}

		// DPI awareness を有効化
		detail::SetDPIAwareness(m_user32);

		// hInstance を取得
		m_hInstance = ::GetModuleHandleW(nullptr);
		
		// WindowClass の名前を生成
		m_windowClassName = L"Siv3D App";//FileSystem::ModulePath().toWstr();

		// WindowClass を登録
		detail::RegisterWindowClass(m_hInstance, m_windowClassName.c_str());

		// モニタを取得
		m_monitors = detail::EnumActiveMonitors();
		if (m_monitors.empty())
		{
			throw EngineError(U"EnumActiveMonitors() failed");
		}

		// ウィンドウを作成SW
		const auto& monitor = m_monitors[0];
		const double scale = monitor.getScale();
		m_dpi = monitor.displayDPI;

		m_state.frameBufferSize.x = static_cast<int32>(m_state.clientSize.x * scale);
		m_state.frameBufferSize.y = static_cast<int32>(m_state.clientSize.y * scale);
		const int32 offsetX = Max<int32>(((monitor.workArea.right - monitor.workArea.left) - m_state.frameBufferSize.x) / 2, 0);
		const int32 offsetY = Max<int32>(((monitor.workArea.bottom - monitor.workArea.top) - m_state.frameBufferSize.y) / 2, 0);
		const int32 posX = (monitor.displayRect.left + offsetX);
		const int32 posY = (monitor.displayRect.top + offsetY);
		const uint32 windowStyleFlags = detail::GetWindowStyleFlags(m_state.style);

		RECT windowRect = { posX, posY, (posX + m_state.frameBufferSize.x), (posY + m_state.frameBufferSize.y) };
		::AdjustWindowRectExForDpi(&windowRect, windowStyleFlags, FALSE, 0, m_dpi);

		m_hWnd = ::CreateWindowExW(
			0,
			m_windowClassName.c_str(),
			m_actualTitle.toWstr().c_str(),
			windowStyleFlags,
			windowRect.left, windowRect.top,
			(windowRect.right - windowRect.left), (windowRect.bottom - windowRect.top),
			nullptr, // No parent window
			nullptr, // No menu
			m_hInstance,
			nullptr);

		if (!m_hWnd)
		{
			throw EngineError(U"CreateWindowExW() failed");
		}

		// Disable touch feedback visualization that causes frame rate drops
		detail::DisableTouchFeedbackVisualization(m_hWnd, m_user32);

		::ShowWindow(m_hWnd, SW_SHOW);
	}

	void CWindow::update()
	{
		if constexpr (SIV3D_BUILD(DEBUG))
		{
			setWindowTitle(m_title);
		}
	}

	void CWindow::setWindowTitle(const String& title)
	{
		String newActualTitle = title;
		
		if constexpr (SIV3D_BUILD(DEBUG))
		{
			const String statistics = SIV3D_ENGINE(Profiler)->getSimpleStatistics();
			newActualTitle += U" (Debug Build) | ";
			newActualTitle += statistics;
		}

		if (m_actualTitle != newActualTitle)
		{
			//LOG_VERBOSE(U"SetWindowTextW(\"{}\")"_fmt(newActualTitle));
			::SetWindowTextW(m_hWnd, newActualTitle.toWstr().c_str());
			m_actualTitle.swap(newActualTitle);
		}

		m_title = title;
	}

	const String& CWindow::getWindowTitle() const noexcept
	{
		return m_title;
	}

	void* CWindow::getHandle() const noexcept
	{
		return m_hWnd;
	}

	const WindowState& CWindow::getState() const noexcept
	{
		return m_state;
	}

	void CWindow::onResize(const bool minimized, const bool maximized)
	{
		LOG_TRACE(U"CWindow::onResize(minimized = {}, maximized = {})"_fmt(minimized, maximized));

		if (minimized)
		{
			m_state.minimized = true;
			m_state.maximized = false;
		}
		else if (maximized)
		{
			m_state.minimized = false;
			m_state.maximized = true;
		}
		else
		{
			m_state.minimized = false;
			m_state.maximized = false;
		}
	}

	void CWindow::onFocus(const bool focused)
	{
		LOG_TRACE(U"CWindow::onFocus(focused = {})"_fmt(focused));

		if (!focused)
		{
			SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::WindowDeactivated);
		}

		m_state.focused = focused;
	}

	void CWindow::onFrameBufferResize(const Size& size)
	{
		LOG_TRACE(U"CWindow::onFrameBufferResize(size = {})"_fmt(size));

		if (size.isZero())
		{
			// window minimized
		}
		else
		{
			m_state.frameBufferSize = size;
		}
	}

	void CWindow::onDPIChange(const uint32 dpi, const double scaling, const Point& pos)
	{
		LOG_TRACE(U"CWindow::onDPIChange(dpi = {} ({:.0f}%))"_fmt(dpi, scaling * 100));
		m_dpi = dpi;

		const int32 newClientWidth = static_cast<int32>(m_state.clientSize.x * scaling);
		const int32 newClientHeight = static_cast<int32>(m_state.clientSize.y * scaling);
		const uint32 windowStyleFlags = detail::GetWindowStyleFlags(m_state.style);
		RECT rect
		{
			.left	= pos.x,
			.top	= pos.y,
			.right	= pos.x + newClientWidth,
			.bottom	= pos.y + newClientHeight,
		};
		::AdjustWindowRectExForDpi(&rect, windowStyleFlags, FALSE, 0, dpi);

		const int32 newWindowWidth = (rect.right - rect.left);
		const int32 newWindowHeight = (rect.bottom - rect.top);
		const UINT flags = (SWP_NOACTIVATE | SWP_NOZORDER);

		LOG_VERBOSE(U"SetWindowPos({}, {}, {}, {}, {:#x})"_fmt(
			rect.left, rect.top,
			newWindowWidth, newWindowHeight,
			flags));

		::SetWindowPos(m_hWnd, HWND_TOP,
			rect.left, rect.top,
			newWindowWidth, newWindowHeight,
			flags);

		m_state.scaling = scaling;
	}

	void CWindow::onBoundsUpdate()
	{
		LOG_VERBOSE(U"CWindow::onBoundsUpdate()");

		// bounds
		{
			RECT windowRect;
			::DwmGetWindowAttribute(m_hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &windowRect, sizeof(RECT));
			m_state.bounds = detail::ToRect(windowRect);
			LOG_VERBOSE(U"- bounds: {}"_fmt(m_state.bounds));
		}

		// frame thickness
		{
			const Size frameSize
			{
				getSystemMetrics(SM_CXBORDER),
				getSystemMetrics(SM_CYBORDER)
			};
			m_state.frameSize = frameSize;
			LOG_VERBOSE(U"- frameSize: {}"_fmt(frameSize));
		}

		// title bar height
		{
			const int32 titleBarHeight = (getSystemMetrics(SM_CYCAPTION)
				+ getSystemMetrics(SM_CYFRAME)
				+ getSystemMetrics(SM_CXPADDEDBORDER));
			m_state.titleBarHeight = titleBarHeight;
			LOG_VERBOSE(U"- titleBarHeight: {}"_fmt(titleBarHeight));
		}
	}

	int32 CWindow::getSystemMetrics(const int32 index) const
	{
		if (m_pGetSystemMetricsForDpi)
		{
			return m_pGetSystemMetricsForDpi(index, m_dpi);
		}
		else
		{
			return ::GetSystemMetrics(index);
		}
	}
}
