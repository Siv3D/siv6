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

		m_actualClientSize.x = static_cast<int32>(m_clientSize.x * scale);
		m_actualClientSize.y = static_cast<int32>(m_clientSize.y * scale);
		const int32 offsetX = Max<int32>(((monitor.workArea.right - monitor.workArea.left) - m_actualClientSize.x) / 2, 0);
		const int32 offsetY = Max<int32>(((monitor.workArea.bottom - monitor.workArea.top) - m_actualClientSize.y) / 2, 0);
		const int32 posX = (monitor.displayRect.left + offsetX);
		const int32 posY = (monitor.displayRect.top + offsetY);

		RECT windowRect = { posX, posY, (posX + m_actualClientSize.x), (posY + m_actualClientSize.y) };
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
			LOG_VERBOSE(U"SetWindowTextW(\"{}\")"_fmt(newActualTitle));
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
}
