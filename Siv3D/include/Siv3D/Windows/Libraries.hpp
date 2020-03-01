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
# include <Siv3D/Platform.hpp>

# pragma comment (linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
# pragma comment (lib, "dwmapi")
# pragma comment (lib, "winmm")

# if SIV3D_BUILD(DEBUG)

	// Debug libraries
	# pragma comment (lib, "Siv3D_d")

# else

	// Release libraries
	# pragma comment (lib, "Siv3D")

# endif
