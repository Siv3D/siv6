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
# include <sstream>
# include "Common.hpp"
# include "Error.hpp"
# include "Unicode.hpp"
# include "ParseBool.hpp"
# include "ParseInt.hpp"
# include "ParseFloat.hpp"

namespace s3d
{
	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="text">
	/// 変換する文字列
	/// </param>
	/// <exception cref="ParseError">
	/// パースエラーが発生したときに例外が投げられます。
	/// Thrown when a parsing error occurs
	/// </exception>
	/// <returns>
	/// 文字列から変換されたデータ
	/// </returns>
	template <class Type>
	[[nodiscard]]
	inline Type Parse(StringView s)
	{
		if constexpr (std::is_integral_v<Type>)
		{
			return ParseInt<Type>(s);
		}
		else if constexpr (std::is_floating_point_v<Type>)
		{
			return ParseFloat<Type>(s);
		}
		else
		{
			Type to;

			if (!(std::wistringstream{ Unicode::ToWstring(s) } >> to))
			{
				throw ParseError(U"Parse(\"{}\") failed"_fmt(s));
			}

			return to;
		}
	}
}
