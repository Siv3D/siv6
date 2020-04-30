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
# include <iostream>

namespace s3d
{
	struct None_t
	{
		struct init {};

		explicit constexpr None_t(init) {}

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const None_t&)
		{
			const CharType no[] = { 'n','o','n','e','\0' };
			return output << no;
		}
	};

	/// <summary>
	/// 無効値
	/// </summary>
	inline constexpr None_t none{ None_t::init() };
}
