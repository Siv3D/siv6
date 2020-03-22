﻿//-----------------------------------------------
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
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Common/ApplicationOptions.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/System/ISystem.hpp>
# include <Siv3D/Error.hpp>

void PerformTest();
void Main();

namespace s3d
{
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
		Main();
	}
}

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	if (g_ApplicationOptions.debugHeapManager)
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

	using namespace s3d;
	Siv3DEngine engine;

	try
	{
		Siv3DEngine::Get<ISiv3DSystem>()->init();
	}
	catch (const Error&)
	{
		return -1;
	}

	if (g_ApplicationOptions.runTest)
	{
		PerformTest();
	}

	const std::future<void> f = std::async(std::launch::async, MainThread);

	while (!f._Is_ready())
	{
		PumpMessages();

		::timeBeginPeriod(1);
		::Sleep(1);
		::timeEndPeriod(1);
	}

	return 0;
}
