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

# include "ApplicationOptions.hpp"

ApplicationOptions g_ApplicationOptions;

namespace s3d
{
	namespace detail
	{
		int EnableDebugHeapManager(const bool enabled) noexcept
		{
			return g_ApplicationOptions.debugHeapManager = enabled;
		}

		int EnableHeadlessMode(const bool enabled) noexcept
		{
			return g_ApplicationOptions.headlessMode = enabled;
		}

		int EnableStdErr(const bool enabled) noexcept
		{
			return g_ApplicationOptions.stdErr = enabled;
		}

		int EnableTest(const bool enabled) noexcept
		{
			return g_ApplicationOptions.runTest = enabled;
		}
	}
}
