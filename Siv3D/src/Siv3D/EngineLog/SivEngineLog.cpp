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
# include <Siv3D/String.hpp>
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

		ScopedEngineLog::ScopedEngineLog(const LogType type, const StringView s)
			: m_type(type)
			, m_s(s)
		{
			Siv3DEngine::Get<ISiv3DLogger>()->write(m_type, m_s + U" ---"_s);
		}

		ScopedEngineLog::~ScopedEngineLog()
		{
			Siv3DEngine::Get<ISiv3DLogger>()->write(m_type, U"--- "_s + m_s);
		}
	}
}
