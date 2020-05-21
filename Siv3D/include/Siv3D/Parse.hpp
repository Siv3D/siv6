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

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="str">
	/// 変換する文字列
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータの Optional, 失敗した場合は none
	/// </returns>
	template <class Type>
	[[nodiscard]]
	inline Optional<Type> ParseOpt(StringView s);

	template <>
	[[nodiscard]]
	inline Optional<bool> ParseOpt<bool>(StringView s);

	template <>
	[[nodiscard]]
	inline Optional<char> ParseOpt<char>(StringView s);

	template <>
	[[nodiscard]]
	inline Optional<char32> ParseOpt<char32>(StringView s);

	template <>
	[[nodiscard]]
	inline Optional<String> ParseOpt<String>(StringView s);

	/// <summary>
	/// 文字列をデータ型に変換します。
	/// </summary>
	/// <param name="text">
	/// 変換する文字列
	/// </param>
	/// <param name="defaultValue">
	/// 変換に失敗した場合に返す値
	/// </param>
	/// <returns>
	/// 文字列から変換されたデータの, 失敗した場合は defaultValue
	/// </returns>
	template <class Type, class U>
	[[nodiscard]]
	Type ParseOr(StringView s, U&& defaultValue);
}

# include "detail/Parse.ipp"
