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
# include "CLogger.hpp"

namespace s3d
{
	CLogger::CLogger()
	{

	}

	CLogger::~CLogger()
	{
	
	}

	void CLogger::write(const LogType type, const StringView s)
	{
		//const int64 timeStamp = Time::GetMillisec() - g_applicationTime;

		type;

		const String output = U"{}\n"_fmt(s);

		std::lock_guard lock(m_mutex);
		{
			::OutputDebugStringW(output.toWstr().c_str());
		}
	}
}
