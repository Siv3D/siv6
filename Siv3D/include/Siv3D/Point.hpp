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
		constexpr bool operator ==(const Point& p) const noexcept
		{
			return (x == p.x) && (y == p.y);
		}

		[[nodiscard]]
		constexpr bool operator !=(const Point& p) const noexcept
		{
			return (x != p.x) || (y != p.y);
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
