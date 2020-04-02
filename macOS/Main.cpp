
# include <Siv3D.hpp>

SIV3D_OPTION_DEBUG_HEAP_MANAGER(true);
SIV3D_OPTION_HEADLESS_MODE(true);
SIV3D_OPTION_OUTPUT_STDERR(true);
SIV3D_OPTION_RUN_TEST(false);

void Main()
{
	int32 frameCount = 0;
	
	while (System::Update())
	{
		Window::SetTitle(frameCount);
		
		System::Sleep(16);
		
		if (++frameCount > 60*8)
		{
			System::Exit();
		}
	}
}
