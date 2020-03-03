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
# include <Siv3D/String.hpp>

namespace s3d
{
	namespace detail
	{
		//
		// UTF-8
		//

		[[nodiscard]]
		size_t UTF8_Length(char32 codePoint) noexcept;

		[[nodiscard]]
		size_t UTF8_Length(StringView s) noexcept;

		void UTF8_Encode(char8** s, char32 codePoint) noexcept;


		//
		// UTF-16
		//

		[[nodiscard]]
		size_t UTF16_Length(char32 codePoint) noexcept;

		[[nodiscard]]
		size_t UTF16_Length(StringView s) noexcept;

		void UTF16_Encode(char16** s, char32 codePoint) noexcept;
	}
}
