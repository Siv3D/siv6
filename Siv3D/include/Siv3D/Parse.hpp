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
# include <typeinfo>
# include "Common.hpp"
# include "Error.hpp"
# include "Unicode.hpp"
# include "ParseBool.hpp"
# include "ParseInt.hpp"
# include "ParseFloat.hpp"
# include "Demangle.hpp"

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
	inline Type Parse(StringView s);

	template <>
	[[nodiscard]]
	inline bool Parse<bool>(StringView s);

	template <>
	[[nodiscard]]
	inline char Parse<char>(StringView s);

	template <>
	[[nodiscard]]
	inline char32 Parse<char32>(StringView s);

	template <>
	[[nodiscard]]
	inline String Parse<String>(StringView s);
}

# include "detail/Parse.ipp"
