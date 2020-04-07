
# include <Siv3D.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(false);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);

void Main()
{
	//Window::SetStyle(WindowStyle::Frameless);
	Window::SetStyle(WindowStyle::Sizable);
	Window::SetMinimumFrameBufferSize(Size(600, 300));

	while (System::Update())
	{
		Window::SetTitle(Window::GetState().frameBufferSize);

		if (Scene::FrameCount() == 400)
		{
			//Window::SetStyle(WindowStyle::Sizable);
		}
	}
}
