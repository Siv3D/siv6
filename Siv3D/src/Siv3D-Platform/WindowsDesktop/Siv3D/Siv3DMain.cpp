//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <crtdbg.h>
# include <future>
# include <Siv3D/Error.hpp>
# include <Siv3D/Format.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ApplicationOptions.hpp>
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/System/CSystem.hpp>
# include <Siv3D/Window/CWindow.hpp>

void Main();

//        [THREAD #0]                        [THREAD #1]
//                            
// WinMain() {                 
//   f = std::async(MainThread)       || MainThread() {
//   **LOCK**                         ||   Siv3DEngine engine;
//                                    ||   engine->System->init();
//                                    <=   **LOCK**
//   engine->Window->init();          ||
//   **LOCK**                         =>
//                                    ||   engine->System->init2();
//                                    <=
//   while (!f._Is_ready()) {         ||   Main() { while(System::Update()) {} } // User code
//     PumMessages();                 ||
//                                    ||   engine::~Siv3DEngine() {
//     if (g_callWindowDestroy) {     ||     ...
//       engine->Window->destroy();   ||     g_callWindowDestroy = true
//       g_callWindowDestroy = false; ||     |
//     }                              ||     wait until (g_callWindowDestroy == false)
//                                    ||     ...  
//     Sleep(1);                      ||   }
//   }                                || }  
// }

namespace s3d
{
	namespace
	{
		std::condition_variable g_cv;
		std::mutex g_mutex;
		int g_initStep = 0;
		bool g_hasError = false;
	}

	std::atomic<bool> g_callWindowDestroy{ false };

	static void PumpMessages()
	{
		for (int32 i = 0; i < 100; ++i)
		{
			MSG message = {};

			if (::PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
			{
				::TranslateMessage(&message);
				::DispatchMessageW(&message);
			}
			else
			{
				return;
			}
		}
	}

	static void MainThread()
	{
		Siv3DEngine engine;

		std::unique_lock ul(g_mutex); // (1)--

		try
		{
			SIV3D_ENGINE(System)->init();
		}
		catch (const Error& error)
		{
			::OutputDebugStringW(U"{}\n"_fmt(error).toWstr().c_str());
			g_hasError = true;

			ul.unlock(); // --(1)
			g_cv.notify_one();
			return;
		}

		g_initStep = 1;

		ul.unlock(); // --(1)
		g_cv.notify_one();
		ul.lock();

		g_cv.wait(ul, []() { return ((g_initStep == 2) || g_hasError); }); // (3)--

		if (g_hasError)
		{
			return;
		}

		try
		{
			dynamic_cast<CSystem*>(SIV3D_ENGINE(System))->init2();
		}
		catch (const Error& error)
		{
			::OutputDebugStringW(U"{}\n"_fmt(error).toWstr().c_str());
			g_hasError = true;
			ul.unlock(); // --(3)
			g_cv.notify_one();
			return;
		}

		g_initStep = 3;

		ul.unlock(); // --(3)
		g_cv.notify_one();

		// (4b)--

		LOG_TRACE(U"Main() ---");

		Main();

		LOG_TRACE(U"--- Main()");
	}
}

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	using namespace s3d;

	if (g_applicationOptions.debugHeap == EngineOption::DebugHeap::Yes)
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

	std::unique_lock ul(g_mutex); // (0)--

	const std::future<void> f = std::async(std::launch::async, MainThread);

	g_cv.wait(ul, [&]() { return ((g_initStep == 1) || g_hasError); }); // --(0) (2)--

	if (g_hasError)
	{
		return -1;
	}

	try
	{
		SIV3D_ENGINE(Window)->init();
	}
	catch (const Error& error)
	{
		::OutputDebugStringW(U"{}\n"_fmt(error).toWstr().c_str());
		g_hasError = true;
		return -1;
	}

	g_initStep = 2;

	ul.unlock(); // --(2)
	g_cv.notify_one();
	ul.lock();

	g_cv.wait(ul, []() { return ((g_initStep == 3) || g_hasError); }); // (4a)--

	if (g_hasError)
	{
		while (!f._Is_ready())
		{
			if (g_callWindowDestroy)
			{
				if (auto pCWindow = dynamic_cast<CWindow*>(SIV3D_ENGINE(Window)))
				{
					pCWindow->destroy();
				}
				
				g_callWindowDestroy = false;
			}

			::Sleep(1);
		}

		return -1;
	}

	while (!f._Is_ready())
	{
		PumpMessages();

		if (g_callWindowDestroy)
		{
			if (auto pCWindow = dynamic_cast<CWindow*>(SIV3D_ENGINE(Window)))
			{
				pCWindow->destroy();
			}

			g_callWindowDestroy = false;
		}

		::timeBeginPeriod(1);
		{
			::Sleep(1);
		}
		::timeEndPeriod(1);
	}

	return 0;
}
