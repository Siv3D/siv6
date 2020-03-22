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
	};

	using Size = Point;
}
