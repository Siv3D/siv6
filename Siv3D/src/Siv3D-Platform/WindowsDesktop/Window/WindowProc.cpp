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
				LOG_TRACE(U"WM_SYSCOMMAND");

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
				const double scale = (static_cast<double>(newDPI) / USER_DEFAULT_SCREEN_DPI);
				
				const int32 newWindowWidth = static_cast<int32>(800 * scale);
				const int32 newWindowHeight = static_cast<int32>(600 * scale);

				LOG_TRACE(U"- New DPI: {} ({:.0f}%)"_fmt(newDPI, scale * 100));

				RECT rect = *reinterpret_cast<const RECT*>(lParam);
				rect.right = rect.left + newWindowWidth;
				rect.bottom = rect.top + newWindowHeight;

				::AdjustWindowRectExForDpi(&rect, WS_OVERLAPPEDWINDOW, FALSE, 0, newDPI);

				LOG_VERBOSE(U"SetWindowPos({}, {}, {}, {}, {:#x})"_fmt(
					rect.left,
					rect.top,
					(rect.right - rect.left),
					(rect.bottom - rect.top),
					(SWP_NOACTIVATE | SWP_NOZORDER)));

				::SetWindowPos(hWnd, HWND_TOP,
					rect.left,
					rect.top,
					(rect.right - rect.left),
					(rect.bottom - rect.top),
					(SWP_NOACTIVATE | SWP_NOZORDER));
				return 1;
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
