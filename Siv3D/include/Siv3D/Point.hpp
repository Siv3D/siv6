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
# include "FormatData.hpp"

namespace s3d
{
	template <class Type> struct Vector2D;
	using Float2 = Vector2D<float>;
	using Vec2 = Vector2D<double>;

	struct Point
	{
		using value_type = int32;

		value_type x, y;

		SIV3D_NODISCARD_CXX20
		Point() = default;

		SIV3D_NODISCARD_CXX20
		constexpr Point(const Point&) = default;

		SIV3D_NODISCARD_CXX20
		constexpr Point(value_type _x, value_type _y) noexcept
			: x(_x)
			, y(_y) {}



		[[nodiscard]]
		constexpr Point operator *(const int32 s) const noexcept
		{
			return{ x * s, y * s };
		}

		[[nodiscard]]
		constexpr Float2 operator *(float s) const noexcept;

		[[nodiscard]]
		constexpr Vec2 operator *(double s) const noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const Point& lhs, const Point& rhs) noexcept
		{
			return (lhs.x == rhs.x) && (lhs.y == rhs.y);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const Point& lhs, const Point& rhs) noexcept
		{
			return (lhs.x != rhs.x) || (lhs.y != rhs.y);
		}

		[[nodiscard]]
		constexpr bool isZero() const noexcept
		{
			return ((x == 0) && (y == 0));
		}



		template <class CharType>
		friend std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType>& output, const Point& value)
		{
			return output << CharType('(')
				<< value.x << CharType(',') << CharType(' ')
				<< value.y << CharType(')');
		}

		template <class CharType>
		friend std::basic_istream<CharType>& operator >>(std::basic_istream<CharType>& input, Point& value)
		{
			CharType unused;
			return input >> unused
				>> value.x >> unused
				>> value.y >> unused;
		}
	};

	using Size = Point;

	void Formatter(FormatData& formatData, const Point& value);
}
