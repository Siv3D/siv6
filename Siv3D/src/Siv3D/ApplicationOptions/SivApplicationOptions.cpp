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

# include <Siv3D/ApplicationOptions.hpp>

namespace s3d
{
	ApplicationOptions g_applicationOptions;

	namespace detail
	{
		int SetEngineOption(const EngineOption::DebugHeap value) noexcept
		{
			g_applicationOptions.debugHeap = value;
			return 0;
		}

		int SetEngineOption(const EngineOption::StdErr value) noexcept
		{
			g_applicationOptions.stdErr = value;
			return 0;
		}

		int SetEngineOption(const EngineOption::Renderer value) noexcept
		{
			g_applicationOptions.renderer = value;
			return 0;
		}
	}
}
