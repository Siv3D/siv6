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
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/UserAction.hpp>
# include <Siv3D/UserAction/IUSerAction.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "WindowProc.hpp"
# include "CWindow.hpp"

namespace s3d
{
	namespace detail
	{
		inline constexpr Rect ToRect(const RECT& rect)
		{
			return Rect(rect.left, rect.top, (rect.right - rect.left), (rect.bottom - rect.top));
		}
	}

	LRESULT CALLBACK WindowProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
	{
		switch (message)
		{
		case WM_CLOSE:
			{
				LOG_TRACE(U"WM_CLOSE");

				SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::CloseButtonClicked);

				return 0; // WM_DESTROY を発生させない
			}
		case WM_KILLFOCUS:
			{
				LOG_TRACE(U"WM_KILLFOCUS");

				SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::WindowDeactivated);
				
				break;
			}
		case WM_KEYDOWN:
			{
				LOG_TRACE(U"WM_KEYDOWN");

				if (wParam == VK_ESCAPE) // Escape key
				{
					SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::AnyKeyDown | UserAction::EscapeKeyDown);
				}
				else if ((VK_BACK <= wParam) || (wParam == VK_CANCEL)) // Key
				{
					SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::AnyKeyDown);
				}
				else if ((VK_LBUTTON <= wParam) && (wParam <= VK_XBUTTON2)) // Mouse button
				{
					SIV3D_ENGINE(UserAction)->reportUserActions(UserAction::MouseButtonDown);
				}

				break;
			}
		case WM_SYSCOMMAND:
			{
				LOG_VERBOSE(U"WM_SYSCOMMAND");

				switch (wParam & 0xffF0)
				{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
				}

				break;
			}
		case WM_DISPLAYCHANGE:
			{
				LOG_TRACE(U"WM_DISPLAYCHANGE");
				
				return 1;
			}
		case WM_DPICHANGED:
			{
				LOG_TRACE(U"WM_DPICHANGED");

				const int32 newDPI = HIWORD(wParam);
				const double scaling = (static_cast<double>(newDPI) / USER_DEFAULT_SCREEN_DPI);
				
				const RECT rect = *reinterpret_cast<const RECT*>(lParam);
				const Point pos(rect.left, rect.top);
				
				dynamic_cast<CWindow*>(SIV3D_ENGINE(Window))->onDPIChange(newDPI, scaling, pos);

				return 1;
			}
		case WM_SIZE:
			{
				LOG_TRACE(U"WM_SIZE");

				auto pCWindow = dynamic_cast<CWindow*>(SIV3D_ENGINE(Window));

				RECT windowRect = {};
				::GetWindowRect(hWnd, &windowRect);
				pCWindow->onBoundsUpdate(detail::ToRect(windowRect));

				const bool minimized = (wParam == SIZE_MINIMIZED);
				const bool maximized = (wParam == SIZE_MAXIMIZED)
					|| (pCWindow->getState().maximized && (wParam != SIZE_RESTORED));
				pCWindow->onResize(minimized, maximized);

				const Size frameBufferSize(LOWORD(lParam), HIWORD(lParam));
				pCWindow->onFrameBufferResize(frameBufferSize);

				return 0;
			}
		case WM_MOVE:
			{
				LOG_VERBOSE(U"WM_MOVE");

				RECT windowRect = {};
				::GetWindowRect(hWnd, &windowRect);
				dynamic_cast<CWindow*>(SIV3D_ENGINE(Window))->onBoundsUpdate(detail::ToRect(windowRect));

				return 0;
			}
		case WM_DESTROY:
			{
				LOG_TRACE(U"WM_DESTROY");

				::PostQuitMessage(0);

				return 0;
			}
		case WM_DEVICECHANGE:
			{
				LOG_TRACE(U"WM_DEVICECHANGE");

				/*
				if (CSystem* system = dynamic_cast<CSystem*>(Siv3DEngine::Get<ISiv3DSystem>()))
				{
					system->onDeviceChange();
				}
				*/

				break;
			}
		}

		return ::DefWindowProcW(hWnd, message, wParam, lParam);
	}
}
