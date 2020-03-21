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
	class String;

	namespace detail
	{
		inline constexpr size_t FormatFloatBufferSize = 384;

		[[nodiscard]]
		String FormatFloat(double value, int32 decimalPlace, bool fixed);

		[[nodiscard]]
		size_t FormatFloat(char32(&dst)[FormatFloatBufferSize], double value, int32 decimalPlace, bool fixed);
	}
}
