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
# include "Date.hpp"

namespace s3d
{
	/// @brief 日付と時刻 | Date and time
	struct DateTime : Date
	{
		/// @brief 時 [0-23]
		int32 hour;

		/// @brief 分 [0-59]
		int32 minute;

		/// @brief 秒 [0-59]
		int32 second;

		/// @brief ミリ秒 [0-999]
		int32 milliseconds;

		/// @brief デフォルトコンストラクタ
		SIV3D_NODISCARD_CXX20
		DateTime() noexcept = default;

		SIV3D_NODISCARD_CXX20
		constexpr DateTime(
			int32 _year,
			int32 _month,
			int32 _day,
			int32 _hour = 0,
			int32 _minute = 0,
			int32 _second = 0,
			int32 _milliseconds = 0) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr DateTime(
			const Date& date,
			int32 _hour = 0,
			int32 _minute = 0,
			int32 _second = 0,
			int32 _milliseconds = 0) noexcept;
	};

	[[nodiscard]]
	String FormatDateTime(const DateTime& dateTime, StringView format);
}

# include "detail/DateTime.ipp"
