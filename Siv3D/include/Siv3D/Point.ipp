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
	inline constexpr Float2 Point::operator * (const float s) const noexcept
	{
		return{ x * s, y * s };
	}

	inline constexpr Vec2 Point::operator * (const double s) const noexcept
	{
		return{ x * s, y * s };
	}
}
