
# include <Siv3D.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(false);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);

void Main()
{
	//Window::SetStyle(WindowStyle::Frameless);
	Window::SetStyle(WindowStyle::Sizable);
	//Window::SetMinimumFrameBufferSize(Size(600, 300));

	//Window::SetPos(100, 100);
	//Window::Resize(400, 300);

	while (System::Update())
	{
		Window::SetTitle(U"F{} V{} s:{}"_fmt(
			Window::GetState().frameBufferSize,
			Window::GetState().virtualSize,
			Window::GetState().scaling));

		//if (Scene::FrameCount() == 100)
		//{
		//	Window::Maximize();
		//}

		//if (Scene::FrameCount() == 200)
		//{
		//	Window::Minimize();
		//}

		//if (Scene::FrameCount() == 300)
		//{
		//	Window::Restore();
		//}


		//if (Scene::FrameCount() == 100)
		//{
		//	Window::SetStyle(WindowStyle::Frameless);
		//}

		//if (Scene::FrameCount() == 200)
		//{
		//	Window::SetPos(200, 200);
		//}

		//if (Scene::FrameCount() == 300)
		//{
		//	Window::SetStyle(WindowStyle::Sizable);
		//}

		//if (Scene::FrameCount() == 400)
		//{
		//	Window::SetPos(3200, 200);
		//}

		//if (Scene::FrameCount() == 500)
		//{
		//	Window::SetStyle(WindowStyle::Frameless);
		//}

		//if (Scene::FrameCount() == 600)
		//{
		//	Window::SetPos(3300, 300);
		//}

		//if (Scene::FrameCount() == 500)
		//{
		//	Window::SetStyle(WindowStyle::Sizable);
		//}

		//if (Scene::FrameCount() == 800)
		//{
		//	Window::SetPos(100, 100);
		//}

		//if (Scene::FrameCount() == 900)
		//{
		//	Window::SetStyle(WindowStyle::Frameless);
		//}
	}
}
