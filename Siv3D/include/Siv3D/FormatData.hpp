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
# include "String.hpp"

namespace s3d
{
	struct FormatData
	{
		struct DecimalPlaces
		{
			static constexpr int32 DefaultDecimalPlaces = 5;

			int32 value;

			SIV3D_NODISCARD_CXX20
			explicit constexpr DecimalPlaces(int32 v = DefaultDecimalPlaces) noexcept
				: value(v) {}
		};

		String string;

		DecimalPlaces decimalPlaces;
	};

	[[nodiscard]]
	constexpr FormatData::DecimalPlaces DecimalPlaces(int32 width) noexcept
	{
		return FormatData::DecimalPlaces(width);
	}

	inline namespace Literals
	{
		inline namespace DecimalPlaceLiterals
		{
			[[nodiscard]]
			constexpr FormatData::DecimalPlaces operator ""_dp(unsigned long long width) noexcept
			{
				return DecimalPlaces(static_cast<int32>(width));
			}
		}
	}
}
