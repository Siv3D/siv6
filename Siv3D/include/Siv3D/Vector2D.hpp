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
	struct Point;

	template <class Type>
	struct Vector2D
	{
		using value_type = Type;

		static constexpr size_t Dimension = 2;

		value_type x, y;

		Vector2D() = default;

		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(value_type _x, value_type _y) noexcept;

		template <class X, class Y>
		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(X _x, Y _y) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(Point p) noexcept;

		template <class U>
		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(const Vector2D<U>& v) noexcept;

		[[nodiscard]]
		constexpr value_type elem(size_t index) const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator +() const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator -() const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator +(Vector2D v) const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator -(Vector2D v) const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator *(value_type s) const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator *(Vector2D v) const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator /(value_type s) const noexcept;

		[[nodiscard]]
		constexpr Vector2D operator /(Vector2D v) const noexcept;

		constexpr Vector2D& operator +=(Vector2D v) noexcept;

		constexpr Vector2D& operator -=(Vector2D v) noexcept;

		constexpr Vector2D& operator *=(value_type s) noexcept;

		constexpr Vector2D& operator *=(Vector2D v) noexcept;

		constexpr Vector2D& operator /=(value_type s) noexcept;

		constexpr Vector2D& operator /=(Vector2D v) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(Vector2D lhs, Vector2D rhs) noexcept
		{
			return (lhs.x == rhs.x) && (lhs.y == rhs.y);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(Vector2D lhs, Vector2D rhs) noexcept
		{
			return (lhs.x != rhs.x) || (lhs.y != rhs.y);
		}

		//[[nodiscard]]
		//constexpr bool epsilonEquals(Vector2D other, value_type epsilon) const noexcept;

		//[[nodiscard]]
		//constexpr bool hasSameDirection(Vector2D other) const noexcept;

		//[[nodiscard]]
		//constexpr bool hasOppositeDirection(Vector2D other) const noexcept;

		[[nodiscard]]
		constexpr bool isZero() const noexcept;

		[[nodiscard]]
		bool hasNaN() const noexcept;

		constexpr Vector2D& set(value_type _x, value_type _y) noexcept;

		constexpr Vector2D& set(Vector2D v) noexcept;

		[[nodiscard]]
		constexpr Vector2D movedBy(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		constexpr Vector2D movedBy(Vector2D v) const noexcept;

		constexpr Vector2D& moveBy(value_type _x, value_type _y) noexcept;

		constexpr Vector2D& moveBy(Vector2D v) noexcept;

		//[[nodiscard]]
		//Vector2D clamped(const RectF& rect) const noexcept;

		//Vector2D& clamp(const RectF& rect) noexcept;

		[[nodiscard]]
		constexpr value_type dot(Vector2D v) const noexcept;

		[[nodiscard]]
		constexpr value_type cross(Vector2D v) const noexcept;

		[[nodiscard]]
		value_type distanceFrom(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		value_type distanceFrom(Vector2D v) const noexcept;

		[[nodiscard]]
		constexpr value_type distanceFromSq(value_type _x, value_type _y) const noexcept;

		[[nodiscard]]
		constexpr value_type distanceFromSq(Vector2D v) const noexcept;

		[[nodiscard]]
		value_type length() const noexcept;

		[[nodiscard]]
		constexpr value_type lengthSq() const noexcept;

		[[nodiscard]]
		value_type lengthInv() const noexcept;

		Vector2D& setLength(value_type _length) noexcept;

		[[nodiscard]]
		Vector2D limitLength(value_type maxLength) const noexcept;



		[[nodiscard]]
		constexpr Point asPoint() const noexcept;
	};

	using Float2	= Vector2D<float>;
	using Vec2		= Vector2D<double>;
	using SizeF		= Vec2;
}
