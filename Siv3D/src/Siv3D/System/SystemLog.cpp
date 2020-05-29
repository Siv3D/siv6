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

# include "SystemLog.hpp"
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Version.hpp>
# include <Siv3D/DateTime.hpp>

namespace s3d
{
	namespace SystemLog
	{
		void Initial()
		{
			LOG_INFO(U"ℹ️ {}"_fmt(DateTime::Now()));

			if constexpr (SIV3D_BUILD(DEBUG))
			{
				LOG_INFO(U"ℹ️ Siv3D Engine (" SIV3D_VERSION U") " SIV3D_PLATFORM_NAME U" [Debug build]");
			}
			else
			{
				LOG_INFO(U"ℹ️ Siv3D Engine (" SIV3D_VERSION U") " SIV3D_PLATFORM_NAME U" [Release build]");
			}

			LOG_INFO(U"⌛ Preparing for setup...");
		}

		void Final()
		{
			LOG_INFO(U"✅ Siv3D engine has terminated");

			LOG_INFO(U"ℹ️ {}"_fmt(DateTime::Now()));
		}
	}
}
