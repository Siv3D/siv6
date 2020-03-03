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

# include <Siv3D.hpp>
# define CATCH_CONFIG_RUNNER
# define CATCH_CONFIG_FAST_COMPILE
# include <Catch2/catch.hpp>

# if SIV3D_PLATFORM(WINDOWS)
#	include <conio.h>
# endif

using namespace s3d;

void PerformTest()
{
	Console.open();

	Catch::Session().run();

# if SIV3D_PLATFORM(WINDOWS)

	_getch();

# endif
}
