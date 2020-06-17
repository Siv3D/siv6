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
	inline constexpr ColorF::ColorF(const double _r, const double _g, const double _b, const double _a) noexcept
		: r(_r)
		, g(_g)
		, b(_b)
		, a(_a) {}

	inline constexpr ColorF::ColorF(const double rgb, const double _a) noexcept
		: r(rgb)
		, g(rgb)
		, b(rgb)
		, a(_a) {}
}
