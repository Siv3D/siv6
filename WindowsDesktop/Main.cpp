
# include <Siv3D.hpp> // OpenSiv3D v0.6
SIV3D_SET(EngineOption::Renderer::Direct3D11)
//SIV3D_SET(EngineOption::Renderer::OpenGL)
SIV3D_SET(EngineOption::D3D11Driver::Hardware)

void Siv3DTest();

void Main()
{
	Window::SetStyle(WindowStyle::Sizable);
	//Siv3DTest();

	//LicenseManager::ShowInBrowser();

	//Scene::SetResizeMode(ResizeMode::Actual);

	Window::Resize(1200, 800);

	Texture t1, t2;
	Console << t1.id().value();
	Console << (t1 == t2);
	Texture t3(Image(32, 32, Palette::Yellow));
	Console << t3.id().value();

	while (System::Update())
	{
		for (auto i : step(20))
		{
			Rect(Cursor::Pos().movedBy(0 + i * 20, 0), 20, 400)
				.draw(HSV(i * 10, 0.5, 0.9));
		}
	}
}
