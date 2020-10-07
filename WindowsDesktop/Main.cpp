﻿
# include <Siv3D.hpp> // OpenSiv3D v0.6
SIV3D_SET(EngineOption::Renderer::Direct3D11)
//SIV3D_SET(EngineOption::Renderer::OpenGL)
SIV3D_SET(EngineOption::D3D11Driver::Hardware)

void Siv3DTest();



struct CustomClock : ISteadyClock
{
	Stopwatch m_stopwatch{ true };

	uint64 getMicrosec() override
	{
		return m_stopwatch.us();
	}

	void pause()
	{
		m_stopwatch.pause();
	}

	void resume()
	{
		m_stopwatch.resume();
	}
};

void Main()
{
	CustomClock customClock;
	Stopwatch s1(true);
	Stopwatch s2(true, &customClock);
	Stopwatch s3(true, &customClock);

	while (System::Update())
	{
		if (Scene::FrameCount() == 200)
		{
			customClock.pause();
		}
		else if (Scene::FrameCount() == 300)
		{
			customClock.resume();
		}

		if (4s < s1)
		{
			return;
		}

		Window::SetTitle(U"{}, {}, {}"_fmt(s1, s2, s3));
	}
}


