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
# include "Common.hpp"

namespace s3d
{
	struct UTF8toUTF32_Converter
	{
	private:

		char8 m_buffer[4];

		uint32 m_count = 0;

		char32 m_result = 0;

	public:

		[[nodiscard]]
		bool put(char8 code) noexcept;

		[[nodiscard]]
		char32 get() const noexcept;
	};
}

# include "detail/UnicodeConverter.ipp"
