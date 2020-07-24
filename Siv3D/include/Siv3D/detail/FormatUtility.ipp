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
	namespace detail
	{
		[[nodiscard]]
		String ThousandsSeparateInt(String&& value, StringView separator);

		[[nodiscard]]
		String ThousandsSeparateFloat(String&& value, StringView separator);
	}

	template <class Type>
	inline String Pad(const Type& value, std::pair<int32, char32> padding)
	{
		return Format(value).lpadded(padding.first, padding.second);
	}

# if __cpp_lib_concepts
	template <Concept::Integral Integer>
# else
	template <class Integer, std::enable_if_t<std::is_integral_v<Integer>>*>
# endif
	inline String ThousandsSeparate(const Integer value, const StringView separator)
	{
		return detail::ThousandsSeparateInt(FormatInt(value), separator);
	}

# ifdef __cpp_lib_concepts
	template <Concept::FloatingPoint FloatingPoint>
# else
	template <class FloatingPoint, std::enable_if_t<std::is_floating_point_v<FloatingPoint>>*>
# endif
	inline String ThousandsSeparate(const FloatingPoint value, const int32 decimalPlace, const bool fixed, const StringView separator)
	{
		return detail::ThousandsSeparateFloat(fixed ? ToFixed(value, decimalPlace) : ToString(value, decimalPlace), separator);
	}
}
