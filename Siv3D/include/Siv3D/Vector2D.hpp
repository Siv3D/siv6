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
	template <class Type>
	struct Vector2D
	{
		using value_type = Type;

		value_type x, y;

		Vector2D() = default;

		template <class X, class Y>
		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(X _x, Y _y) noexcept
			: x(static_cast<value_type>(_x))
			, y(static_cast<value_type>(_y)) {}

		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(value_type _x, value_type _y) noexcept
			: x(_x)
			, y(_y) {}

		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(const Point& v) noexcept
			: x(static_cast<value_type>(v.x))
			, y(static_cast<value_type>(v.y)) {}

		template <class U>
		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(const Vector2D<U>& v) noexcept
			: x(static_cast<value_type>(v.x))
			, y(static_cast<value_type>(v.y)) {}
	};

	using Float2 = Vector2D<float>;
	using Vec2 = Vector2D<double>;
	using SizeF = Vec2;
}
