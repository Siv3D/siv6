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
# include "../Utility.hpp"
# include "../Hash.hpp"

namespace s3d
{
	inline constexpr DateTime::DateTime(
		const int32 _year,
		const int32 _month,
		const int32 _day,
		const int32 _hour,
		const int32 _minute,
		const int32 _second,
		const int32 _milliseconds) noexcept
		: Date(_year, _month, _day)
		, hour(_hour)
		, minute(_minute)
		, second(_second)
		, milliseconds(_milliseconds) {}

	constexpr DateTime::DateTime(
		const Date& date,
		const int32 _hour,
		const int32 _minute,
		const int32 _second,
		const int32 _milliseconds) noexcept
		: Date(date)
		, hour(_hour)
		, minute(_minute)
		, second(_second)
		, milliseconds(_milliseconds) {}
}
