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
# include <Siv3D/Window.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <GLFW/glfw3.h>

namespace s3d
{
	class CWindow final : public ISiv3DWindow
	{
	private:
		
		GLFWwindow* m_window = nullptr;
		
		Size m_clientSize = Window::DefaultClientSize;
		
		String m_title = String(Window::DefaultTitle);
		String m_actualTitle = String(SIV3D_BUILD(DEBUG) ? U"Siv3D App (Debug Build)"_sv : Window::DefaultTitle);

	public:

		CWindow();

		~CWindow() override;

		void init() override;
		
		void update() override;
		
		void setWindowTitle(const String& title) override;

		const String& getWindowTitle() const noexcept override;
	};
}
