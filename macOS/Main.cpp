
# include <Siv3D.hpp>
SIV3D_SET(EngineOption::Renderer,	RendererType::Metal)

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
