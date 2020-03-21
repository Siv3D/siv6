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
# include "Fwd.hpp"
# include "PredefinedNamedParameter.hpp"
# include "LetterCase.hpp"

namespace s3d
{
	[[nodiscard]]
	String ToString(int8 value);

	[[nodiscard]]
	String ToString(uint8 value);

	[[nodiscard]]
	String ToString(int16 value);

	[[nodiscard]]
	String ToString(uint16 value);

	[[nodiscard]]
	String ToString(int32 value);

	[[nodiscard]]
	String ToString(uint32 value);

	[[nodiscard]]
	String ToString(long value);

	[[nodiscard]]
	String ToString(unsigned long value);

	[[nodiscard]]
	String ToString(long long value);

	[[nodiscard]]
	String ToString(unsigned long long value);


	[[nodiscard]]
	String ToString(char value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(int8 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(uint8 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(int16 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(uint16 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(int32 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(uint32 value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(long value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(unsigned long value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(long long value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);

	[[nodiscard]]
	String ToString(unsigned long long value, Arg::radix_<uint32> radix, LetterCase letterCase = LetterCase::Upper);


# ifdef __cpp_lib_concepts
	template <Concept::Integral Integer>
# else
	template <class Integer>
# endif
	[[nodiscard]]
	inline String ToBinary(Integer value)
	{
		return ToString(value, Arg::radix = 2);
	}

# ifdef __cpp_lib_concepts
	template <Concept::Integral Integer>
# else
	template <class Integer>
# endif
	[[nodiscard]]
	inline String ToOctal(Integer value)
	{
		return ToString(value, Arg::radix = 8);
	}

# ifdef __cpp_lib_concepts
	template <Concept::Integral Integer>
# else
	template <class Integer>
# endif
	[[nodiscard]]
	inline String ToHex(Integer value, LetterCase letterCase = LetterCase::Upper)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}
}
