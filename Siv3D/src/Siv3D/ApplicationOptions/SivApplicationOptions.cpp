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
		int SetEngineOption(const EngineOption option, const int value) noexcept
		{
			switch (option)
			{
			case EngineOption::DebugHeap:
				g_applicationOptions.debugHeap	= static_cast<bool>(value);
				break;
			case EngineOption::StdErr:
				g_applicationOptions.stdErr		= static_cast<bool>(value);
				break;
			default:
				break;
			}

			return 0;
		}

		int SetEngineOption(const EngineOption option, const RendererType value) noexcept
		{
			if (option == EngineOption::Renderer)
			{
				g_applicationOptions.renderer = value;
			}
			
			return 0;
		}
	}
}
