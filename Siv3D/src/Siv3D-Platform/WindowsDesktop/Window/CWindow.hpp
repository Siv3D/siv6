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
# include <Siv3D/WindowState.hpp>
# include "Monitor.hpp"

namespace s3d
{
	class CWindow final : public ISiv3DWindow
	{
	private:

		HWND m_hWnd = nullptr;
		HINSTANCE m_hInstance = nullptr;
		std::wstring m_windowClassName;
		
		String m_title = String(Window::DefaultTitle);
		String m_actualTitle = String(SIV3D_BUILD(DEBUG) ? U"Siv3D App (Debug Build)"_sv : Window::DefaultTitle);

		Array<Monitor> m_monitors;

		WindowState m_state;

	public:

		CWindow();

		~CWindow() override;

		void init() override;

		void update() override;

		void setWindowTitle(const String& title) override;

		const String& getWindowTitle() const noexcept override;

		void* getHandle() const noexcept override;

		const WindowState& getState() const noexcept override;

		void onResize(bool minimized, bool maximized);

		void onFocus(bool focused);

		void onFrameBufferResize(const Size& size);

		void onDPIChange(int32 dpi, double scaling, const Point& pos);

		void onBoundsUpdate();
	};
}
