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
	template <class Type>
	template <class X, class Y>
	inline constexpr Vector2D<Type>::Vector2D(X _x, Y _y) noexcept
		: x(static_cast<value_type>(_x))
		, y(static_cast<value_type>(_y)) {}

	template <class Type>
	inline constexpr Vector2D<Type>::Vector2D(value_type _x, value_type _y) noexcept
		: x(_x)
		, y(_y) {}

	template <class Type>
	inline constexpr Vector2D<Type>::Vector2D(Point p) noexcept
		: x(static_cast<value_type>(p.x))
		, y(static_cast<value_type>(p.y)) {}

	template <class Type>
	template <class U>
	inline constexpr Vector2D<Type>::Vector2D(const Vector2D<U>& v) noexcept
		: x(static_cast<value_type>(v.x))
		, y(static_cast<value_type>(v.y)) {}

	template <class Type>
	inline constexpr Point Vector2D<Type>::asPoint() const noexcept
	{
		return{ static_cast<Point::value_type>(x), static_cast<Point::value_type>(y) };
	}
}
