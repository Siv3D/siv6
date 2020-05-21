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
# include <cstdint>
# include <cstddef> // for size_t

namespace s3d
{
	/// @brief Signed integer type with width of 8 bits
	using int8 = std::int8_t;

	/// @brief Signed integer type with width of 16 bits
	using int16 = std::int16_t;

	/// @brief Signed integer type with width of 32 bits
	using int32 = std::int32_t;

	/// @brief Signed integer type with width of 64 bits
	using int64 = std::int64_t;

	/// @brief Unsigned integer type with width of 8 bits
	using uint8 = std::uint8_t;

	/// @brief Unsigned integer type with width of 16 bits
	using uint16 = std::uint16_t;

	/// @brief Unsigned integer type with width of 32 bits
	using uint32 = std::uint32_t;

	/// @brief Unsigned integer type with width of 64 bits
	using uint64 = std::uint64_t;

	/// @brief UTF-8 character
	using char8 = char;

	/// @brief UTF-16 character
	using char16 = char16_t;
	static_assert(sizeof(char16) == 2);

	/// @brief UTF-32 character
	using char32 = char32_t;
	static_assert(sizeof(char32) == 4);
}
