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

# pragma once
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Window.hpp>
# include "Monitor.hpp"

namespace s3d
{
	class CWindow final : public ISiv3DWindow
	{
	private:

		HWND m_hWnd = nullptr;
		HINSTANCE m_hInstance = nullptr;
		std::wstring m_windowClassName;
		String m_actualTitle = SIV3D_BUILD(DEBUG) ? U"Siv3D App (Debug Build)" : U"Siv3D App";

		Array<Monitor> m_monitors;
		Size m_clientSize = Window::DefaultClientSize;
		uint32 m_style = WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME);

	public:

		CWindow();

		~CWindow() override;

		void init() override;
	};
}
