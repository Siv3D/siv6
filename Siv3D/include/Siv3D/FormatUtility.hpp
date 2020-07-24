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
# include "Format.hpp"

namespace s3d
{
	template <class Type>
	[[nodiscard]]
	inline String Pad(const Type& value, const std::pair<int32, char32>& padding);

	[[nodiscard]]
	String FormatDataSize(int64 bytes);

# if __cpp_lib_concepts
	template <Concept::Integral Integer>
# else
	template <class Integer, std::enable_if_t<std::is_integral_v<Integer>>* = nullptr>
# endif
	[[nodiscard]]
	inline String ThousandsSeparate(Integer value, StringView separator = U","_sv);

# ifdef __cpp_lib_concepts
	template <Concept::FloatingPoint FloatingPoint>
# else
	template <class FloatingPoint, std::enable_if_t<std::is_floating_point_v<FloatingPoint>>* = nullptr>
# endif
	[[nodiscard]]
	inline String ThousandsSeparate(FloatingPoint value, int32 decimalPlace = 3, bool fixed = false, StringView separator = U","_sv);
}

# include "detail/FormatUtility.ipp"
