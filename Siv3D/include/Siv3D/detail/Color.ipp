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
	inline constexpr Color::Color(const uint32 _r, const uint32 _g, const uint32 _b, const uint32 _a) noexcept
		: r(_r)
		, g(_g)
		, b(_b)
		, a(_a) {}

	inline constexpr Color::Color(const uint32 rgb, const uint32 _a) noexcept
		: r(rgb)
		, g(rgb)
		, b(rgb)
		, a(_a) {}

	inline constexpr Color::Color(const Color rgb, const uint32 _a) noexcept
		: r(rgb.r)
		, g(rgb.g)
		, b(rgb.b)
		, a(_a) {}

	inline constexpr Color::Color(const ColorF& color) noexcept
		: r(Color::ToUint8(color.r))
		, g(Color::ToUint8(color.g))
		, b(Color::ToUint8(color.b))
		, a(Color::ToUint8(color.a)) {}

	inline constexpr Color Color::operator ~() const noexcept
	{
		return{ static_cast<uint8>(~r),
				static_cast<uint8>(~g),
				static_cast<uint8>(~b),
				a };
	}

	inline constexpr uint8 Color::ToUint8(const double x) noexcept
	{
		if (x >= 1.0)
		{
			return 255;
		}
		else if (x <= 0.0)
		{
			return 0;
		}
		else
		{
			return static_cast<uint8>(x * 255.0 + 0.5);
		}
	}
}
