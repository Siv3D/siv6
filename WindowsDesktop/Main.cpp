
# include <Siv3D.hpp> // OpenSiv3D v0.6
SIV3D_SET(EngineOption::Renderer::Direct3D11)
//SIV3D_SET(EngineOption::Renderer::OpenGL)
SIV3D_SET(EngineOption::D3D11Driver::Hardware)

void Siv3DTest();

void Main()
{
	//Siv3DTest();
	//LicenseManager::ShowInBrowser();

	//Window::SetStyle(WindowStyle::Sizable);
	//Scene::SetResizeMode(ResizeMode::Actual);
	//Window::Resize(1200, 800);

	while (System::Update())
	{
		//if (Scene::FrameCount() == 200)
		//{
		//	Window::Resize(600, 400);
		//}

		for (auto i : step(20))
		{
			Rect(Cursor::Pos().movedBy(0 + i * 20, 0), 20, 400)
				.draw(HSV(i * 10, 0.5, 0.9));
		}
	}
}
