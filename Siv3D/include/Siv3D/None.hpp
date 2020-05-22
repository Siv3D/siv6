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
# include "Common.hpp"
# include "FormatData.hpp"

namespace s3d
{
	/// @brief 無効値を表現する型
	struct None_t
	{
		struct init {};

		SIV3D_NODISCARD_CXX20
		explicit constexpr None_t(init) {}

		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const None_t&)
		{
			const CharType no[] = { 'n','o','n','e','\0' };
			return output << no;
		}

		friend void Formatter(FormatData& formatData, None_t)
		{
			formatData.string.append(U"none"_sv);
		}
	};

	/// @brief 無効値
	inline constexpr None_t none{ None_t::init() };
}
