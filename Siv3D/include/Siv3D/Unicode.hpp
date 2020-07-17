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
# include "StringView.hpp"

namespace s3d
{
	class String;

	/// <summary>
	/// 文字列のエンコードの変換
	/// </summary>
	namespace Unicode
	{
		/// <summary>
		/// ASCII 文字列を String に変換します。
		/// </summary>
		/// <param name="asciiText">
		/// ASCII 文字で構成された文字列
		/// </param>
		/// <remarks>
		/// Widen() 関数より高速に動作します。
		/// </remarks>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		String WidenAscii(std::string_view asciiText);

		/// <summary>
		/// 文字列を String に変換します。
		/// </summary>
		/// <param name="s">
		/// 変換する文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		String Widen(std::string_view s);

		/// <summary>
		/// ワイド文字列を String に変換します。
		/// </summary>
		/// <param name="s">
		/// 変換するワイド文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		String FromWstring(std::wstring_view s);

		/// <summary>
		/// UTF-8 文字列を String に変換します。
		/// </summary>
		/// <param name="s">
		/// 変換する UTF-8 文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		String FromUTF8(std::string_view s);

		/// <summary>
		/// UTF-16 文字列を String に変換します。
		/// </summary>
		/// <param name="s">
		/// 変換する UTF-16 文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		String FromUTF16(std::u16string_view s);

		/// <summary>
		/// UTF-32 文字列を String に変換します。
		/// </summary>
		/// <param name="s">
		/// 変換する UTF-32 文字列
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>	
		[[nodiscard]]
		String FromUTF32(std::u32string_view s);

		/// <summary>
		/// ASCII 文字列を std::string に変換します。
		/// </summary>
		/// <param name="asciiText">
		/// ASCII 文字で構成された文字列
		/// </param>
		/// <remarks>
		/// Narrow() 関数より高速に動作します。
		/// </remarks>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		std::string NarrowAscii(StringView asciiText);

		/// <summary>
		/// String を std::string に変換します。
		/// </summary>
		/// <param name="s">
		/// String
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		std::string Narrow(StringView s);

		/// <summary>
		/// String を std::wstring に変換します。
		/// </summary>
		/// <param name="s">
		/// String
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		std::wstring ToWstring(StringView s);

		/// <summary>
		/// String を UTF-8 文字列に変換します。
		/// </summary>
		/// <param name="s">
		/// String
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		std::string ToUTF8(StringView s);

		/// <summary>
		/// String を UTF-16 文字列に変換します。
		/// </summary>
		/// <param name="s">
		/// String
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		std::u16string ToUTF16(StringView s);

		/// <summary>
		/// String を UTF-32 文字列に変換します。
		/// </summary>
		/// <param name="s">
		/// String
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		std::u32string ToUTF32(StringView s);

		[[nodiscard]]
		inline constexpr bool IsHighSurrogate(const char16 ch) noexcept;

		[[nodiscard]]
		inline constexpr bool IsLowSurrogate(const char16 ch) noexcept;
	}
}

# include "detail/Unicode.ipp"
