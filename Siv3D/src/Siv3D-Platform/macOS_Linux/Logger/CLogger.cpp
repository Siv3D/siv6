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

# include <array>
# include <Siv3D/String.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Time.hpp>
# include "CLogger.hpp"

namespace s3d
{
	namespace detail
	{
		constexpr std::array<StringView, 7> LogTypeNames =
		{
			U"[error]   "_sv,
			U"[fail]    "_sv,
			U"[warning] "_sv,
			U""_sv,
			U"[info]    "_sv,
			U"[trace]   "_sv,
			U"[verbose] "_sv,
		};
	}

	const int64 g_applicationTime = Time::GetMillisec();

	CLogger::CLogger()
	{

	}

	CLogger::~CLogger()
	{
	
	}

	void CLogger::write(const LogType type, const StringView s)
	{
		const int64 timeStamp = Time::GetMillisec() - g_applicationTime;
		const StringView logTypeName = detail::LogTypeNames[FromEnum(type)];
		const std::string output = U"{}: {}{}\n"_fmt(timeStamp, logTypeName, s).narrow();

		std::lock_guard lock(m_mutex);
		{
			std::cout << output;
		}
	}
}
