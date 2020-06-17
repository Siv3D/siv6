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
		inline constexpr size_t Uint32Width = (std::numeric_limits<uint32>::digits10 + 1);

		inline constexpr size_t Int32Width = (std::numeric_limits<int32>::digits10 + 2);

		void AppendUint32(char32** p, uint32 value);

		void AppendInt32(char32** p, int32 value);
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
