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

struct ApplicationOptions
{
	bool debugHeapManager = false;
	bool headlessMode = false;
	bool stdErr = false;
};

extern ApplicationOptions g_ApplicationOptions;
