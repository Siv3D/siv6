
# include <Siv3D.hpp>

SIV3D_SET(EngineOption::StdErr,		true)
SIV3D_SET(EngineOption::Renderer,	RendererType::Headless) // 非グラフィックモード

void Siv3DTest();

void Main()
{
	Siv3DTest();
}
