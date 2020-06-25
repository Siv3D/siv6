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
	template <Concept::Arithmetic Arithmetic>
# else
	template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>*>
# endif
	inline constexpr Mat3x2::Mat3x2(const Arithmetic s) noexcept
		: _11(static_cast<value_type>(s)), _12(0.0f)
		, _21(0.0f), _22(static_cast<value_type>(s))
		, _31(0.0f), _32(0.0f) {}

	inline constexpr Mat3x2::Mat3x2(const float _11, const float _12, const float _21, const float _22, const float _31, const float _32) noexcept
		: _11(_11), _12(_12)
		, _21(_21), _22(_22)
		, _31(_31), _32(_32) {}

	inline constexpr Mat3x2 Mat3x2::Identity() noexcept
	{
		return{ 1.0f, 0.0f,
				0.0f, 1.0f,
				0.0f, 0.0f };
	}

	inline constexpr Mat3x2 Mat3x2::Translate(const Float2 v) noexcept
	{
		return{ 1.0f, 0.0f,
				0.0f, 1.0f,
				v.x, v.y };
	}

	template <class X, class Y>
	inline constexpr Mat3x2 Mat3x2::Translate(const X x, const Y y) noexcept
	{
		return{ 1.0f, 0.0f,
				0.0f, 1.0f,
				static_cast<value_type>(x), static_cast<value_type>(y) };
	}

	inline constexpr Mat3x2 Mat3x2::Scale(const Float2 scale, const Float2 center) noexcept
	{
		return{ scale.x, 0.0f,
				0.0f, scale.y,
				(center.x - scale.x * center.x), (center.y - scale.y * center.y) };
	}

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic>
# else
	template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>*>
# endif
	inline constexpr Mat3x2 Mat3x2::Scale(const Arithmetic s, const Float2 center) noexcept
	{
		return{ static_cast<value_type>(s), 0.0f,
				0.0f, static_cast<value_type>(s),
				(center.x - s * center.x), (center.y - s * center.y) };
	}

	template <class X, class Y>
	inline constexpr Mat3x2 Mat3x2::Scale(const X sx, const Y sy, const Float2 center) noexcept
	{
		return{ static_cast<value_type>(sx), 0.0f,
				0.0f, static_cast<value_type>(sy),
				(center.x - sx * center.x), (center.y - sy * center.y) };
	}

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic>
# else
	template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>*>
# endif
	inline Mat3x2 Mat3x2::Rotate(const Arithmetic angle, const Float2 center) noexcept
	{
		const float s = std::sin(static_cast<value_type>(angle));
		const float c = std::cos(static_cast<value_type>(angle));
		return{ c, s,
				-s, c,
				(center.x - center.x * c + center.y * s), (center.y - center.x * s - center.y * c) };
	}

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic>
# else
	template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>*>
# endif
	inline constexpr Mat3x2 Mat3x2::ShearX(const Arithmetic sx) noexcept
	{
		return{ 1.0f, 0.0f,
				-static_cast<value_type>(sx), 1.0f,
				0.0f, 0.0f };
	}

# if __cpp_lib_concepts
	template <Concept::Arithmetic Arithmetic>
# else
	template <class Arithmetic, std::enable_if_t<std::is_arithmetic_v<Arithmetic>>*>
# endif
	inline constexpr Mat3x2 Mat3x2::ShearY(const Arithmetic sy) noexcept
	{
		return{ 1.0f, static_cast<value_type>(sy),
				0.0f, 1.0f,
				0.0f, 0.0f };
	}

	template <class X, class Y>
	inline constexpr Mat3x2 Mat3x2::Screen(const X width, const Y height) noexcept
	{
		return{ (2.0f / static_cast<value_type>(width)), 0.0f,
				0.0f, (-2.0f / static_cast<value_type>(height)),
				-1.0f, 1.0f };
	}

	inline constexpr Mat3x2 Mat3x2::Screen(const Float2 size) noexcept
	{
		return{ (2.0f / size.x), 0.0f,
				0.0f, (-2.0f / size.y),
				-1.0f, 1.0f };
	}








	inline constexpr Float2 Mat3x2::transform(const Point pos) const noexcept
	{
		return
		{
			(pos.x * _11 + pos.y * _21 + _31),
			(pos.x * _12 + pos.y * _22 + _32)
		};
	}

	inline constexpr Float2 Mat3x2::transform(const Float2 pos) const noexcept
	{
		return
		{
			(pos.x * _11 + pos.y * _21 + _31),
			(pos.x * _12 + pos.y * _22 + _32)
		};
	}

	inline constexpr Vec2 Mat3x2::transform(const Vec2 pos) const noexcept
	{
		return
		{
			(pos.x * _11 + pos.y * _21 + _31),
			(pos.x * _12 + pos.y * _22 + _32)
		};
	}
}
