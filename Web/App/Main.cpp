
# include <Siv3D.hpp>
# include <emscripten.h>

void RunMainLoop(void* arg)
{
	static_cast<const std::function<void()>*>(arg)->operator()();
}

void SetMainLoop(std::function<void()> mainLoop)
{
	emscripten_set_main_loop_arg(RunMainLoop, reinterpret_cast<void*>(&mainLoop), 0, 1);
}

void Main()
{
	SetMainLoop([&]() {
		if (System::Update())
		{
			for (auto i : step(20))
			{
				Rect(Cursor::Pos().movedBy(0 + i * 20, 0), 20, 400)
					.draw(HSV(i * 10, 0.5, 0.9));
			}
		}
	});	
}

