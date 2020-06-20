
# include <Siv3D.hpp> // OpenSiv3D v0.6

SIV3D_SET_OPTION(DebugHeap,	true)
SIV3D_SET_OPTION(StdErr,	true)
SIV3D_SET_OPTION(Renderer,	RendererType::OpenGL)

void Main()
{
	while (System::Update())
	{
		for (auto i : step(20))
		{
			Rect(20 + i * 20, 20, 20, 400)
				.draw(HSV(i * 10, 0.5, 0.9));
		}
	}
}
