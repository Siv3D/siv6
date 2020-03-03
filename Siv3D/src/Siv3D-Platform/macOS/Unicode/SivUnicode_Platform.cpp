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

# include <Siv3D/Unicode.hpp>

namespace s3d
{
	namespace Unicode
	{
		std::string Narrow(const StringView s)
		{
			return ToUTF8(s);
		}

		std::wstring ToWstring(const StringView s)
		{
			return std::wstring(s.begin(), s.end());
		}
	}
}
