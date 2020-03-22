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
# include "CWindow.hpp"
# include "WindowProc.hpp"

namespace s3d
{
	namespace detail
	{
		static void RegisterWindowClass(HINSTANCE hInstance, const wchar_t* className)
		{
			LOG_TRACE(U"RegisterWindowClass() ---");

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

			LOG_TRACE(U"--- RegisterWindowClass()");
		}
	}

	CWindow::CWindow()
	{

	}

	CWindow::~CWindow()
	{
		LOG_TRACE(U"CWindow::~CWindow() ---");

		if (m_hWnd)
		{
			LOG_VERBOSE(U"DestroyWindow()");
			::DestroyWindow(m_hWnd);
		}

		LOG_VERBOSE(U"UnregisterClassW()");
		::UnregisterClassW(m_windowClassName.c_str(), m_hInstance);

		LOG_TRACE(U"--- CWindow::~CWindow()");
	}

	void CWindow::init()
	{
		LOG_TRACE(U"CWindow::init() ---");

		m_hInstance = ::GetModuleHandleW(nullptr);
		
		m_windowClassName = L"Siv3D App";//FileSystem::ModulePath().toWstr();

		detail::RegisterWindowClass(m_hInstance, m_windowClassName.c_str());

		m_monitors = detail::EnumActiveMonitors();

		LOG_TRACE(U"--- CWindow::init()");
	}
}
