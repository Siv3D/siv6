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
# include "Platform.hpp"
# include "LogType.hpp"

namespace s3d
{
	class StringView;

	namespace Internal
	{
		void OutputEngineLog(LogType type, StringView s);
	}
}

# if SIV3D_BUILD(DEBUG)

#	define LOG_TEST(S)		s3d::Internal::OutputEngineLog(s3d::LogType::App,		S)
#	define LOG_ERROR(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Error,		S)
#	define LOG_FAIL(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Fail,		S)
#	define LOG_WARNING(S)	s3d::Internal::OutputEngineLog(s3d::LogType::Warning,	S)
#	define LOG_INFO(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Info,		S)
#	define LOG_TRACE(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Trace,		S)
#	define LOG_VERBOSE(S)	s3d::Internal::OutputEngineLog(s3d::LogType::Verbose,	S)

# else

#	define LOG_ERROR(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Error,		S)
#	define LOG_FAIL(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Fail,		S)
#	define LOG_WARNING(S)	s3d::Internal::OutputEngineLog(s3d::LogType::Warning,	S)
#	define LOG_INFO(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Info,		S)
#	define LOG_TRACE(S)		s3d::Internal::OutputEngineLog(s3d::LogType::Trace,		S)
#	define LOG_VERBOSE(S)	((void)0)

# endif
