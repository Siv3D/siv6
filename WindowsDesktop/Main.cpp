
# include <Siv3D.hpp> // OpenSiv3D v0.6
SIV3D_SET(EngineOption::Renderer::OpenGL)

void Siv3DTest();

void Main()
{
	//Siv3DTest();

	Console << Resource(U"engine/shader/glsl/test.vert");
	Console << Resource(U"engine/shader/glsl/test2.vert");
	Console << FileSystem::Size(U"/engine/shader/glsl/test.vert");
	Console << FileSystem::FileSize(U"/engine/shader/glsl/test.vert");
	Console << FileOrResource(U"engine/shader/glsl/test.vert");
	SetResourceOption(ResourceOption::Resource);
	Console << FileOrResource(U"engine/shader/glsl/test.vert");

	while (System::Update())
	{
		for (auto i : step(20))
		{
			Rect(Cursor::Pos().movedBy(0 + i * 20, 0), 20, 400)
				.draw(HSV(i * 10, 0.5, 0.9));
		}
	}
}
