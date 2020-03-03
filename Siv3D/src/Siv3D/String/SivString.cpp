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

# include <Siv3D/String.hpp>
# include <Siv3D/Unicode.hpp>

namespace s3d
{
	std::string String::narrow() const
	{
		return Unicode::Narrow(m_string);
	}

	std::wstring String::toWstr() const
	{
		return Unicode::ToWstring(m_string);
	}
}
