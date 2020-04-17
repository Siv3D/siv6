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

namespace s3d
{
# if __cpp_lib_concepts
	template <Concept::Integral Integer>
# else
	template <class Integer, std::enable_if_t<std::is_integral_v<Integer>>*>
# endif
	inline constexpr Byte operator <<(const Byte value, const Integer shift) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(value) << shift));
	}

# if __cpp_lib_concepts
	template <Concept::Integral Integer>
# else
	template <class Integer, std::enable_if_t<std::is_integral_v<Integer>>*>
# endif
	inline constexpr Byte operator >>(const Byte value, const Integer shift) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(value) >> shift));
	}

	inline constexpr Byte operator |(const Byte x, const Byte y) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(x) | static_cast<unsigned int>(y)));
	}

	inline constexpr Byte operator &(const Byte x, const Byte y) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(x) & static_cast<unsigned int>(y)));
	}

	inline constexpr Byte operator ^(const Byte x, const Byte y) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(static_cast<unsigned int>(x) ^ static_cast<unsigned int>(y)));
	}

	inline constexpr Byte operator ~(const Byte value) noexcept
	{
		return static_cast<Byte>(static_cast<unsigned char>(~static_cast<unsigned int>(value)));
	}

# if __cpp_lib_concepts
	template <Concept::Integral Integer>
# else
	template <class Integer, std::enable_if_t<std::is_integral_v<Integer>>*>
# endif
	inline constexpr Byte& operator <<=(Byte& value, const Integer shift) noexcept
	{
		return value = (value << shift);
	}

# if __cpp_lib_concepts
	template <Concept::Integral Integer>
# else
	template <class Integer, std::enable_if_t<std::is_integral_v<Integer>>*>
# endif
	inline constexpr Byte& operator >>=(Byte& value, const Integer shift) noexcept
	{
		return value = (value >> shift);
	}

	inline constexpr Byte& operator |=(Byte& x, const Byte y) noexcept
	{
		return x = (x | y);
	}

	inline constexpr Byte& operator &=(Byte& x, const Byte y) noexcept
	{
		return x = (x & y);
	}

	inline constexpr Byte& operator ^=(Byte& x, const Byte y) noexcept
	{
		return x = (x ^ y);
	}

	inline constexpr uint8 AsUint8(const Byte value) noexcept
	{
		return static_cast<uint8>(value);
	}
}
