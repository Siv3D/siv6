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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/StringView.hpp>
# include <Siv3D/Logger/ILogger.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Internal
	{
		void OutputEngineLog(const LogType type, const StringView s)
		{
			Siv3DEngine::Get<ISiv3DLogger>()->write(type, s);
		}
	}
}
