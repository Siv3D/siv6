
# include <Siv3D.hpp>
# include <emscripten.h>

void Siv3DTest();

void MainLoop()
{
	System::Update();

	for (auto i : step(20))
	{
		Rect(Cursor::Pos().movedBy(0 + i * 20, 0), 20, 400)
			.draw(HSV(i * 10, 0.5, 0.9));
	}
}

void Main()
{	
	// Siv3DTest();
	emscripten_set_main_loop(&MainLoop, 0, 1);
}
