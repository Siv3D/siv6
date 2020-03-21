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

# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Time.hpp>
# include "CLogger.hpp"

namespace s3d
{
	const int64 g_applicationTime = Time::GetMillisec();

	CLogger::CLogger()
	{

	}

	CLogger::~CLogger()
	{
	
	}

	void CLogger::write(const LogType type, const StringView s)
	{
		const int64 timeStamp = (Time::GetMillisec() - g_applicationTime);

		type;

		const std::wstring output = U"{}: {}\n"_fmt(timeStamp, s).toWstr();

		std::lock_guard lock(m_mutex);
		{
			::OutputDebugStringW(output.c_str());
		}
	}
}
