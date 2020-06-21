﻿
# include <Siv3D.hpp> // OpenSiv3D v0.6

SIV3D_SET(EngineOption::DebugHeap,	true)
SIV3D_SET(EngineOption::StdErr,		true)
SIV3D_SET(EngineOption::Renderer,	RendererType::OpenGL)

void Siv3DTest();

void Main()
{
	//Siv3DTest();

	while (System::Update())
	{
		for (auto i : step(1))
		{
			Rect(20 + i * 20, 20, 20, 400)
				.draw(HSV(i * 10, 0.5, 0.9));
		}
	}
}
