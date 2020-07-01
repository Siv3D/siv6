
# include <Siv3D.hpp> // OpenSiv3D v0.6
SIV3D_SET(EngineOption::DebugHeap::Yes)
SIV3D_SET(EngineOption::StdErr::Yes)
SIV3D_SET(EngineOption::Renderer::OpenGL)

void Siv3DTest();

void Main()
{
	while (System::Update())
	{
		for (auto i : step(20))
		{
			Rect(20 + i * 20, 20, 20, 400)
				.draw(HSV(i * 10, 0.5, 0.9));
		}

		Rect(Cursor::Pos(), 50).draw(ColorF(0.25));
	}
}
