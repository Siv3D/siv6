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
# include <Siv3D/Profiler/IProfiler.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "CWindow.hpp"
# include "DPIAwareness.hpp"
# include "WindowProc.hpp"

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
	}

	void CWindow::init()
	{
		LOG_SCOPED_TRACE(U"CWindow::init()");

		// DPI awareness を有効化
		detail::SetDPIAwareness();

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

		m_state.frameBufferSize.x = static_cast<int32>(m_state.clientSize.x * scale);
		m_state.frameBufferSize.y = static_cast<int32>(m_state.clientSize.y * scale);
		const int32 offsetX = Max<int32>(((monitor.workArea.right - monitor.workArea.left) - m_state.frameBufferSize.x) / 2, 0);
		const int32 offsetY = Max<int32>(((monitor.workArea.bottom - monitor.workArea.top) - m_state.frameBufferSize.y) / 2, 0);
		const int32 posX = (monitor.displayRect.left + offsetX);
		const int32 posY = (monitor.displayRect.top + offsetY);

		RECT windowRect = { posX, posY, (posX + m_state.frameBufferSize.x), (posY + m_state.frameBufferSize.y) };
		::AdjustWindowRectExForDpi(&windowRect, WS_OVERLAPPEDWINDOW, FALSE, 0, monitor.displayDPI);

		m_hWnd = ::CreateWindowExW(
			0,
			m_windowClassName.c_str(),
			m_actualTitle.toWstr().c_str(),
			m_style,
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

	void CWindow::onDPIChange(const int32 dpi, const double scaling, const Point& pos)
	{
		LOG_TRACE(U"CWindow::onDPIChange(dpi = {} ({:.0f}%))"_fmt(dpi, scaling * 100));

		const int32 newClientWidth = static_cast<int32>(m_state.clientSize.x * scaling);
		const int32 newClientHeight = static_cast<int32>(m_state.clientSize.y * scaling);

		RECT rect;
		rect.left	= pos.x;
		rect.top	= pos.y;
		rect.right	= pos.x + newClientWidth;
		rect.bottom	= pos.y + newClientHeight;

		::AdjustWindowRectExForDpi(&rect, WS_OVERLAPPEDWINDOW, FALSE, 0, dpi);

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

	void CWindow::onBoundsUpdate(const Rect& rect)
	{
		LOG_VERBOSE(U"CWindow::onBoundsUpdate(rect = {})"_fmt(rect));

		m_state.bounds = rect;
	}
}
