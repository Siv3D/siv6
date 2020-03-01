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

namespace s3d
{
	namespace detail
	{
		int EnableDebugHeapManager(bool);
		int EnableHeadlessMode(bool);
		int EnableStdErr(bool);
	}
}

# define SIV3D_OPTION_DEBUG_HEAP_MANAGER(bool) const int dummy_s3d_enable_debug_heap_manager = s3d::detail::EnableDebugHeapManager(bool)
# define SIV3D_OPTION_HEADLESS_MODE(bool) const int dummy_s3d_enable_headless_mode = s3d::detail::EnableHeadlessMode(bool)
# define SIV3D_OPTION_OUTPUT_STDERR(bool) const int dummy_s3d_enable_stderr = s3d::detail::EnableStdErr(bool)
