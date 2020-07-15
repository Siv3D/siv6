
# include <Siv3D.hpp> // OpenSiv3D v0.6
SIV3D_SET(EngineOption::Renderer::OpenGL)

void Siv3DTest();

void Main()
{
	Siv3DTest();

	while (System::Update())
	{

	}
}
