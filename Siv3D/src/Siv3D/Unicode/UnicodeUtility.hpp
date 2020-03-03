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
		[[nodiscard]]
		size_t UTF8_Length(const char32 codePoint) noexcept;

		[[nodiscard]]
		size_t UTF8_Length(const StringView s) noexcept;

		void UTF8_Encode(char8** s, const char32 codePoint) noexcept;
	}
}
