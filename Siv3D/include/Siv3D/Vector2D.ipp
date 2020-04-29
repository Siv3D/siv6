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
	inline constexpr Vector2D<Type>::Vector2D(value_type _x, value_type _y) noexcept
		: x(_x)
		, y(_y) {}

	template <class Type>
	template <class X, class Y>
	inline constexpr Vector2D<Type>::Vector2D(X _x, Y _y) noexcept
		: x(static_cast<value_type>(_x))
		, y(static_cast<value_type>(_y)) {}

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
	inline constexpr typename Vector2D<Type>::value_type Vector2D<Type>::elem(const size_t index) const noexcept
	{
		if (index == 0)
		{
			return x;
		}
		else if (index == 1)
		{
			return y;
		}
		else
		{
			return 0;
		}
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector2D<Type>::operator +() const noexcept
	{
		return *this;
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector2D<Type>::operator -() const noexcept
	{
		return{ -x, -y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector2D<Type>::operator +(const Vector2D v) const noexcept
	{
		return{ x + v.x, y + v.y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector2D<Type>::operator -(const Vector2D v) const noexcept
	{
		return{ x - v.x, y - v.y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector2D<Type>::operator *(const value_type s) const noexcept
	{
		return{ x * s, y * s };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector2D<Type>::operator *(const Vector2D v) const noexcept
	{
		return{ x * v.x, y * v.y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector2D<Type>::operator /(const value_type s) const noexcept
	{
		return *this * (static_cast<value_type>(1.0) / s);
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector2D<Type>::operator /(const Vector2D v) const noexcept
	{
		return{ x / v.x, y / v.y };
	}

	template <class Type>
	inline constexpr Vector2D<Type>& Vector2D<Type>::operator +=(const Vector2D v) noexcept
	{
		x += v.x; y += v.y;
		return *this;
	}

	template <class Type>
	inline constexpr Vector2D<Type>& Vector2D<Type>::operator -=(const Vector2D v) noexcept
	{
		x -= v.x; y -= v.y;
		return *this;
	}

	template <class Type>
	inline constexpr Vector2D<Type>& Vector2D<Type>::operator *=(const value_type s) noexcept
	{
		x *= s; y *= s;
		return *this;
	}

	template <class Type>
	inline constexpr Vector2D<Type>& Vector2D<Type>::operator *=(const Vector2D v) noexcept
	{
		x *= v.x; y *= v.y;
		return *this;
	}

	template <class Type>
	inline constexpr Vector2D<Type>& Vector2D<Type>::operator /=(const value_type s) noexcept
	{
		return *this *= (static_cast<value_type>(1.0) / s);
	}

	template <class Type>
	inline constexpr Vector2D<Type>& Vector2D<Type>::operator /=(const Vector2D v) noexcept
	{
		x /= v.x; y /= v.y;
		return *this;
	}

	//template <class Type>
	//inline constexpr bool Vector2D<Type>::epsilonEquals(const Vector2D other, const value_type epsilon) const noexcept
	//{

	//}

	template <class Type>
	inline constexpr bool Vector2D<Type>::isZero() const noexcept
	{
		return (x == static_cast<value_type>(0.0))
			&& (y == static_cast<value_type>(0.0));
	}

	template <class Type>
	inline bool Vector2D<Type>::hasNaN() const noexcept
	{
		return std::isnan(x)
			|| std::isnan(y);
	}

	template <class Type>
	inline constexpr Vector2D<Type>& Vector2D<Type>::set(const value_type _x, const value_type _y) noexcept
	{
		x = _x; y = _y;
		return *this;
	}

	template <class Type>
	inline constexpr Vector2D<Type>& Vector2D<Type>::set(const Vector2D v) noexcept
	{
		return *this = v;
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector2D<Type>::movedBy(const value_type _x, const value_type _y) const noexcept
	{
		return{ x + _x, y + _y };
	}

	template <class Type>
	inline constexpr Vector2D<Type> Vector2D<Type>::movedBy(const Vector2D v) const noexcept
	{
		return{ x + v.x, y + v.y };
	}

	template <class Type>
	inline constexpr Vector2D<Type>& Vector2D<Type>::moveBy(const value_type _x, const value_type _y) noexcept
	{
		x += _x; y += _y;
		return *this;
	}

	template <class Type>
	inline constexpr Vector2D<Type>& Vector2D<Type>::moveBy(const Vector2D v) noexcept
	{
		x += v.x; y += v.y;
		return *this;
	}

	template <class Type>
	inline constexpr typename Vector2D<Type>::value_type Vector2D<Type>::dot(const Vector2D v) const noexcept
	{
		return x * v.x + y * v.y;
	}

	template <class Type>
	inline constexpr typename Vector2D<Type>::value_type Vector2D<Type>::cross(const Vector2D v) const noexcept
	{
		return x * v.y - y * v.x;
	}




	template <class Type>
	inline constexpr Point Vector2D<Type>::asPoint() const noexcept
	{
		return{ static_cast<Point::value_type>(x), static_cast<Point::value_type>(y) };
	}
}
