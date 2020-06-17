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
	struct ColorF
	{
		/// @brief 赤 | Red
		double r;

		/// @brief 緑 | Green
		double g;

		/// @brief 青 | Blue
		double b;

		/// @brief アルファ | Alpha
		double a;

		SIV3D_NODISCARD_CXX20
		ColorF() = default;

		SIV3D_NODISCARD_CXX20
		ColorF(const ColorF&) = default;

		SIV3D_NODISCARD_CXX20
		constexpr ColorF(double _r, double _g, double _b, double _a = 1.0) noexcept;

		SIV3D_NODISCARD_CXX20
		explicit constexpr ColorF(double rgb, double _a = 1.0) noexcept;

		[[nodiscard]]
		friend constexpr bool operator ==(const ColorF& lhs, const ColorF& rhs) noexcept
		{
			return (lhs.r == rhs.r)
				&& (lhs.g == rhs.g)
				&& (lhs.b == rhs.b)
				&& (lhs.a == rhs.a);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(const ColorF& lhs, const ColorF& rhs) noexcept
		{
			return (lhs.r != rhs.r)
				|| (lhs.g != rhs.g)
				|| (lhs.b != rhs.b)
				|| (lhs.a != rhs.a);
		}
	};
}
