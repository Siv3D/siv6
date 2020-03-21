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
	std::cout << "OpenSiv3D for macOS\n";
	
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
	
	Main();

	return 0;
}
