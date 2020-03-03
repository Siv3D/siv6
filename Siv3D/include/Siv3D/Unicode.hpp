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
		/// <summary>
		/// String を std::string に変換します。
		/// </summary>
		/// <param name="view">
		/// String
		/// </param>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		std::string Narrow(StringView view);
	}
}
