
# include <Siv3D.hpp>
SIV3D_SET(EngineOption::Renderer::Metal)

void Siv3DTest();

void Main()
{
	Siv3DTest();
	
	//LicenseManager::ShowInBrowser();
	//System::LaunchBrowser(U"test.html");
	//System::LaunchBrowser(U"https://siv3d.github.io/");
	
	while (System::Update())
	{
		for (auto i : step(20))
		{
			Rect(Cursor::Pos().movedBy(0 + i * 20, 0), 20, 400)
				.draw(HSV(i * 10, 0.5, 0.9));
		}
	}
}
