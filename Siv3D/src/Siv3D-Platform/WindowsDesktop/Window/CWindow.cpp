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

		static void DisableTouchFeedbackVisualization(HWND hWND, HMODULE user32)
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

		inline constexpr uint32 GetWindowStyleFlags(const WindowStyle style) noexcept
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

		inline constexpr double GetScaling(uint32 dpi) noexcept
		{
			return (static_cast<double>(dpi) / USER_DEFAULT_SCREEN_DPI);
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

		DLL::UnloadSystemLibrary(m_user32);
	}

	void CWindow::init()
	{
		LOG_SCOPED_TRACE(U"CWindow::init()");

		// user32.dll
		{
			m_user32 = DLL::LoadSystemLibrary(L"user32.dll");
			m_pGetSystemMetricsForDpi = DLL::GetFunctionNoThrow(m_user32, "GetSystemMetricsForDpi");
			m_pAdjustWindowRectExForDpi = DLL::GetFunctionNoThrow(m_user32, "AdjustWindowRectExForDpi");
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
		if (m_monitors = detail::EnumActiveMonitors();
			m_monitors.empty())
		{
			throw EngineError(U"EnumActiveMonitors() failed");
		}

		// ウィンドウを作成
		{
			const auto& monitor = m_monitors[0];
			const double scale = monitor.getScale();
			m_dpi = monitor.displayDPI;

			m_state.frameBufferSize = (m_state.clientSize * scale).asPoint();
			const int32 offsetX = Max<int32>(((monitor.workArea.right - monitor.workArea.left) - m_state.frameBufferSize.x) / 2, 0);
			const int32 offsetY = Max<int32>(((monitor.workArea.bottom - monitor.workArea.top) - m_state.frameBufferSize.y) / 2, 0);
			const Point pos(monitor.displayRect.left + offsetX, monitor.displayRect.top + offsetY);
			const uint32 windowStyleFlags = detail::GetWindowStyleFlags(m_state.style);
			const Rect windowRect = adjustWindowRect(pos, m_state.frameBufferSize, windowStyleFlags);

			m_hWnd = ::CreateWindowExW(
				0,
				m_windowClassName.c_str(),
				m_actualTitle.toWstr().c_str(),
				windowStyleFlags,
				windowRect.x, windowRect.y,
				windowRect.w, windowRect.h,
				nullptr, // No parent window
				nullptr, // No menu
				m_hInstance,
				nullptr);

			if (!m_hWnd)
			{
				throw EngineError(U"CreateWindowExW() failed");
			}
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

	void CWindow::setStyle(const WindowStyle style)
	{
		LOG_SCOPED_TRACE(U"CWindow::setStyle(style = {})"_fmt(FromEnum(style)));

		if (m_state.fullscreen)
		{
		//	m_state.style = style;
		//	setFullscreen(false, unspecified, WindowResizeOption::KeepSceneSize);
			return;
		}

		if (m_state.style == style)
		{
			return;
		}

		const auto current = m_state.style;
		const bool triggerWindowResize = ((current == WindowStyle::Frameless) || (style == WindowStyle::Frameless));
		const uint32 windowStyleFlags = detail::GetWindowStyleFlags(style);
		m_state.style = style;

		::SetWindowLongPtrW(m_hWnd, GWL_STYLE, windowStyleFlags);

		{
			const Point pos = m_state.bounds.pos;
			const double scaling = detail::GetScaling(m_dpi);
			const Size newClientSize = (m_state.clientSize * scaling).asPoint();
			const Rect windowRect = adjustWindowRect(pos, newClientSize, windowStyleFlags);
			const UINT flags = ((triggerWindowResize ? 0 : SWP_NOSIZE) | SWP_NOZORDER | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_FRAMECHANGED);

			setWindowPos(windowRect, flags);
		}

		onBoundsUpdate();

		::ShowWindow(m_hWnd, SW_NORMAL);
	}

	void CWindow::setPos(const Point& pos)
	{
		LOG_SCOPED_TRACE(U"CWindow::setPos(pos = {})"_fmt(pos));

		if (m_state.fullscreen)
		{
			return;
		}

		{
			const double scaling = detail::GetScaling(m_dpi);
			const Size newClientSize = (m_state.clientSize * scaling).asPoint();
			const uint32 windowStyleFlags = detail::GetWindowStyleFlags(m_state.style);
			const Rect windowRect = adjustWindowRect(pos, newClientSize, windowStyleFlags);
			const UINT flags = (SWP_DEFERERASE | SWP_NOOWNERZORDER | SWP_NOZORDER);

			setWindowPos(windowRect, flags);
		}
	}

	void CWindow::maximize()
	{
		LOG_TRACE(U"CWindow::maximize()");

		if (m_state.style == WindowStyle::Fixed)
		{
			LOG_FAIL(U"A window with WindowStyle::Fixed cannot be maximized");
			return;
		}

		::ShowWindow(m_hWnd, SW_MAXIMIZE);
	}

	void CWindow::restore()
	{
		LOG_TRACE(U"CWindow::restore()");
		::ShowWindow(m_hWnd, SW_RESTORE);
	}

	void CWindow::minimize()
	{
		LOG_TRACE(U"CWindow::minimize()");
		::ShowWindow(m_hWnd, SW_MINIMIZE);
	}

	void CWindow::setMinimumFrameBufferSize(const Size& size)
	{
		m_state.minFrameBufferSize = size;
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

	void CWindow::onDPIChange(const uint32 dpi, const Point& suggestedPos)
	{
		const double scaling = detail::GetScaling(m_dpi);
		LOG_SCOPED_TRACE(U"CWindow::onDPIChange()");
		LOG_TRACE(U"- dpi = {}({:.0f}%), suggestedPos = {}"_fmt(dpi, scaling * 100, suggestedPos));

		m_dpi = dpi;
		m_state.scaling = scaling;
		onBoundsUpdate();

		const Size newClientSize = (m_state.clientSize * scaling).asPoint();
		const uint32 windowStyleFlags = detail::GetWindowStyleFlags(m_state.style);
		Rect windowRect = adjustWindowRect(m_state.bounds.pos, newClientSize, windowStyleFlags);
		
		if (m_state.style != WindowStyle::Frameless)
		{
			windowRect.y = (suggestedPos.y - m_state.titleBarHeight);
		}

		constexpr UINT flags = (SWP_NOACTIVATE | SWP_NOZORDER);
		setWindowPos(windowRect, flags);
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
			const Size frameSize(getSystemMetrics(SM_CXBORDER), getSystemMetrics(SM_CYBORDER));
			m_state.frameSize = frameSize;
			LOG_VERBOSE(U"- frameSize: {}"_fmt(frameSize));
		}

		// title bar height
		{
			const int32 titleBarHeight = (getSystemMetrics(SM_CYCAPTION)
				+ getSystemMetrics(SM_CYFRAME) + getSystemMetrics(SM_CXPADDEDBORDER));
			m_state.titleBarHeight = titleBarHeight;
			LOG_VERBOSE(U"- titleBarHeight: {}"_fmt(titleBarHeight));
		}

		// border
		{
			const DWORD windowStyleFlags = ::GetWindowLong(m_hWnd, GWL_STYLE);
			const Rect dummyWindowRect = adjustWindowRect(Point(0, 0), Size(0, 0), windowStyleFlags);		
			m_border = dummyWindowRect.size;
			LOG_VERBOSE(U"- border: {}"_fmt(m_border));
		}
	}

	void CWindow::onMinMaxInfo(LPMINMAXINFO pMinMaxInfo)
	{
		pMinMaxInfo->ptMinTrackSize.x = (m_state.minFrameBufferSize.x + m_border.x);
		pMinMaxInfo->ptMinTrackSize.y = (m_state.minFrameBufferSize.y + m_border.y);
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

	Rect CWindow::adjustWindowRect(const Point& pos, const Size& size, const int32 windowStyleFlags) const
	{
		LOG_VERBOSE(U"CWindow::adjustWindowRect({}, {}, {:#x})"_fmt(pos, size, windowStyleFlags));

		const DWORD windowExStyleFlags = static_cast<DWORD>(::GetWindowLongPtrW(m_hWnd, GWL_EXSTYLE));
		RECT rect = { pos.x, pos.y, (pos.x + size.x), (pos.y + size.y) };

		if (m_pAdjustWindowRectExForDpi)
		{
			m_pAdjustWindowRectExForDpi(&rect, windowStyleFlags, false, windowExStyleFlags, m_dpi);
		}
		else
		{
			::AdjustWindowRectEx(&rect, windowStyleFlags, false, windowExStyleFlags);
		}
		
		return Rect(rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top));
	}

	void CWindow::setWindowPos(const Rect& rect, const UINT flags)
	{
		m_targetWindowPos = rect.pos;

		Point pos = rect.pos;
		if (m_state.style != WindowStyle::Frameless)
		{
			pos.x += m_state.frameSize.x;
			pos.y += m_state.titleBarHeight;
		}
		
		const Size size = rect.size;

		LOG_VERBOSE(U"SetWindowPos({}, {}, {}, {}, {:#x})"_fmt(
			pos.x, pos.y,
			size.x, size.y,
			flags));

		::SetWindowPos(m_hWnd, HWND_TOP,
			pos.x, pos.y,
			size.x, size.y,
			flags);
	}
}
