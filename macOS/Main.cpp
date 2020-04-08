
# include <Siv3D.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(false);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);

void Main()
{
	Window::SetStyle(WindowStyle::Sizable);
	//Window::Resize(400, 400);
	//Window::ResizeFrameBuffer(800, 800);
	//Window::SetStyle(WindowStyle::Frameless);
	
	while (System::Update())
	{
		const String s = U"F{} V{} s:{} B({}, {}) minmax({},{})"_fmt(
		Window::GetState().frameBufferSize,
		Window::GetState().virtualSize,
		Window::GetState().scaling,
		Window::GetState().bounds.pos,
		Window::GetState().bounds.size,
		Window::GetState().minimized,
		Window::GetState().maximized);
		
		Window::SetTitle(s);
		
		if (Scene::FrameCount() == 200)
		{
			//Window::SetPos(200, 200);
		}
		
		Logger << s;
	}
}
