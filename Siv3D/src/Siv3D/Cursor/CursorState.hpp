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
# include <Siv3D/Common.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	struct CursorState
	{
		Point previousRaw = { 0,0 };
		Point currentRaw = { 0,0 };
		Point deltaRaw = { 0,0 };

		Vec2 previousF = { 0,0 };
		Vec2 currentF = { 0,0 };
		Vec2 deltaF = { 0,0 };

		Point previous = { 0,0 };
		Point current = { 0,0 };
		Point delta = { 0,0 };

		constexpr void update(const Point& raw, const Vec2& scaled) noexcept
		{
			{
				previousRaw	= currentRaw;
				currentRaw	= raw;
				deltaRaw	= (currentRaw - previousRaw);
			}

			{
				previousF	= currentF;
				currentF	= scaled;
				deltaF		= (currentF - previousF);
			}

			{
				previous	= previousF.asPoint();
				current		= currentF.asPoint();
				delta		= deltaF.asPoint();
			}
		}
	};
}
