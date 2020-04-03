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
				.hCursor		= nullptr,
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

		const int32 clientWidth = static_cast<int32>(m_clientSize.x * scale);
		const int32 clientHeight = static_cast<int32>(m_clientSize.y * scale);
		const int32 offsetX = Max<int32>(((monitor.workArea.right - monitor.workArea.left) - clientWidth) / 2, 0);
		const int32 offsetY = Max<int32>(((monitor.workArea.bottom - monitor.workArea.top) - clientHeight) / 2, 0);
		const int32 posX = (monitor.displayRect.left + offsetX);
		const int32 posY = (monitor.displayRect.top + offsetY);

		RECT windowRect = { posX, posY, (posX + clientWidth), (posY + clientHeight) };
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

	}

	void CWindow::setWindowTitle(const String& title)
	{
		if (m_title == title)
		{
			return;
		}

		if constexpr (SIV3D_BUILD(DEBUG))
		{
			//const String statistics = Siv3DEngine::Get<ISiv3DProfiler>()->getSimpleStatistics();
			m_actualTitle = title + U" (Debug Build) | ";
		}
		else
		{
			m_actualTitle = title;
		}

		m_title = title;

		::SetWindowTextW(m_hWnd, m_actualTitle.toWstr().c_str());
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
