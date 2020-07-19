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
# include <array>
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

	struct UTF16toUTF32_Converter
	{
	private:

		char32 m_result = 0;

		char16 m_buffer = 0;

		bool m_hasHighSurrogate = false;

	public:

		[[nodiscard]]
		bool put(char16 code) noexcept;

		[[nodiscard]]
		char32 get() const noexcept;
	};

	struct UTF32toUTF8_Converter
	{
	private:

		std::array<char8, 4> m_buffer;

	public:

		[[nodiscard]]
		size_t put(char32 code) noexcept;

		[[nodiscard]]
		const std::array<char8, 4>& get() const noexcept;

		[[nodiscard]]
		std::array<char8, 4>::const_iterator begin() const noexcept;
	};

	struct UTF32toUTF16_Converter
	{
	private:

		std::array<char16, 2> m_buffer;

	public:

		[[nodiscard]]
		size_t put(char32 code) noexcept;

		[[nodiscard]]
		const std::array<char16, 2>& get() const noexcept;

		[[nodiscard]]
		std::array<char16, 2>::const_iterator begin() const noexcept;
	};
}

# include "detail/UnicodeConverter.ipp"
