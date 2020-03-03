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
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Common/ApplicationOptions.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

void PerformTest();
void Main();

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	if (g_ApplicationOptions.debugHeapManager)
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

	using namespace s3d;
	Siv3DEngine engine;

	if (g_ApplicationOptions.runTest)
	{
		PerformTest();
	}

	Main();

	return 0;
}
