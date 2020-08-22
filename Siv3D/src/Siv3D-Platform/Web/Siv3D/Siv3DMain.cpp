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

# include <iostream>
# include <Siv3D/Common/ApplicationOptions.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/System/ISystem.hpp>
# include <Siv3D/Error.hpp>

void PerformTest();
void Main();

int main(int, char*[])
{
	std::cout << "OpenSiv3D for Linux\n";
	
	using namespace s3d;
	Siv3DEngine engine;
	
	try
	{
		SIV3D_ENGINE(System)->init();
	}
	catch (const Error& error)
	{
		std::cout << error << '\n';
		return -1;
	}
	
	if (g_ApplicationOptions.runTest)
	{
		PerformTest();
	}
	
	SIV3D_ENGINE(System)->onMainThreadStart();
	
	Main();

	SIV3D_ENGINE(System)->onMainThreadTerminate();
	
	return 0;
}
