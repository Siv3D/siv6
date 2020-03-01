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

# pragma once
# include <future>
# include <Siv3D/Windows/Windows.hpp>

void Main();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Main();

	return 0;
}
