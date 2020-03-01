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
# include <Common/ApplicationOptions.hpp>

void Main();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if (g_ApplicationOptions.debugHeapManager)
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

	Main();

	return 0;
}
