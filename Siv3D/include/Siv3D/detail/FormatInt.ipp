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
		void AppendInt(char32** p, const long value);
	}

# ifdef __cpp_lib_concepts
	template <Concept::Integral Integer>
# else
	template <class Integer>
# endif
	inline String ToBinary(const Integer value)
	{
		return ToString(value, Arg::radix = 2);
	}

# ifdef __cpp_lib_concepts
	template <Concept::Integral Integer>
# else
	template <class Integer>
# endif
	inline String ToOctal(const Integer value)
	{
		return ToString(value, Arg::radix = 8);
	}

# ifdef __cpp_lib_concepts
	template <Concept::Integral Integer>
# else
	template <class Integer>
# endif
	inline String ToHex(const Integer value, const LetterCase letterCase)
	{
		return ToString(value, Arg::radix = 16, letterCase);
	}
}
