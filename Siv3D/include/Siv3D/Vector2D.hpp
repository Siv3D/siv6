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

		value_type x, y;

		Vector2D() = default;

		template <class X, class Y>
		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(X _x, Y _y) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(value_type _x, value_type _y) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(Point p) noexcept;

		template <class U>
		SIV3D_NODISCARD_CXX20
		constexpr Vector2D(const Vector2D<U>& v) noexcept;



		[[nodiscard]]
		constexpr Point asPoint() const noexcept;
	};

	using Float2	= Vector2D<float>;
	using Vec2		= Vector2D<double>;
	using SizeF		= Vec2;
}
