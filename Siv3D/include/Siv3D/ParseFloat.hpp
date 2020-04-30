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
# include "Optional.hpp"

namespace s3d
{
# ifdef __cpp_lib_concepts
	template <Concept::FloatingPoint FloatingPoint>
# else
	template <class FloatingPoint>
# endif
	[[nodiscard]]
	FloatingPoint ParseFloat(StringView s);

	template <>
	[[nodiscard]]
	float ParseFloat<float>(StringView s);

	template <>
	[[nodiscard]]
	double ParseFloat<double>(StringView s);

	template <>
	[[nodiscard]]
	long double ParseFloat<long double>(StringView s);


# ifdef __cpp_lib_concepts
	template <Concept::FloatingPoint FloatingPoint>
# else
	template <class FloatingPoint>
# endif
	[[nodiscard]]
	Optional<FloatingPoint> ParseFloatOpt(StringView s) noexcept;

	template <>
	[[nodiscard]]
	Optional<float> ParseFloatOpt<float>(StringView s) noexcept;

	template <>
	[[nodiscard]]
	Optional<double> ParseFloatOpt<double>(StringView s) noexcept;

	template <>
	[[nodiscard]]
	Optional<long double> ParseFloatOpt<long double>(StringView s) noexcept;
}
