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

# pragma once
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/Array.hpp>

namespace s3d
{
	struct Monitor
	{
		String adapterString;
		String adapterName;
		String displayString;
		String displayName;
		int32 widthMillimeter = 0;
		int32 heightMillimeter = 0;
		HMONITOR handle = nullptr;
		RECT displayRect = {};
		RECT workArea = {};
		int32 displayDPI = 96;
		bool isPrimaryAdapter = false;
	};

	namespace detail
	{
		BOOL CALLBACK MonitorCallback(HMONITOR handle, HDC, RECT*, LPARAM data);

		Monitor CreateMonitor(const DISPLAY_DEVICEW& adapter, const DISPLAY_DEVICEW* display);

		Array<Monitor> EnumActiveMonitors();
	}
}
