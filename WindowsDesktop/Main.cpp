
# include <Siv3D.hpp> // OpenSiv3D v0.6
SIV3D_SET(EngineOption::Renderer::OpenGL)

void Siv3DTest();

struct Wid {};

void Main()
{
	//Siv3DTest();

	//LicenseManager::ShowInBrowser();

	while (System::Update())
	{
		for (auto i : step(20))
		{
			Rect(Cursor::Pos().movedBy(0 + i * 20, 0), 20, 400)
				.draw(HSV(i * 10, 0.5, 0.9));
		}
	}
}
