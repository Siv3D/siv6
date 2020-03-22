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
# include "String.hpp"

namespace s3d
{
	namespace Unicode
	{
		[[nodiscard]]
		String FromWString(std::wstring_view view);

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
	}
}
