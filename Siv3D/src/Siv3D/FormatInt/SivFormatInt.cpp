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

# include <cstring>
# include <Siv3D/FormatInt.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/IntFormatter.hpp>

namespace s3d
{
	namespace detail
	{
		void AppendInt(char32** const p, const long value)
		{
			bool negative;
			unsigned long val;

			if (value < 0)
			{
				negative = true;
				val = -value;
			}
			else
			{
				negative = false;
				val = value;
			}

			char32 buffer[12];
			char32* pos = &buffer[11];
			*pos = U'\0';

			do
			{
				*(--pos) = U'0' + static_cast<char32>(val % 10);

				val = val / 10;

			} while (val != 0);

			if (negative)
			{
				*(--pos) = U'-';
			}

			const size_t length = &buffer[11] - pos;

			std::memcpy(*p, pos, length * sizeof(char32));

			*p += length;
		}

	# ifdef __cpp_lib_concepts
		template <Concept::UnsignedIntegral UnsignedInteger>
	# else
		template <class UnsignedInteger>
	# endif
		[[nodiscard]]
		inline String ItoW(const UnsignedInteger value, const unsigned radix, const bool isNegative, const LetterCase letterCase)
		{
			if (radix < 2 || 36 < radix)
			{
				return String();
			}

			char32 buffer[std::numeric_limits<UnsignedInteger>::digits];
			char32* p = buffer;
			size_t length = 0;
			UnsignedInteger remaining = value;

			if (isNegative)
			{
				*p++ = '-';
				++length;
				remaining = static_cast<UnsignedInteger>(-static_cast<std::make_signed_t<UnsignedInteger>>(remaining));
			}

			char32* first_digit = p;
			const char32 a = (letterCase == LetterCase::Upper) ? U'A' : U'a';

			do
			{
				const UnsignedInteger digit = static_cast<UnsignedInteger>(remaining % static_cast<UnsignedInteger>(radix));
				remaining /= static_cast<UnsignedInteger>(radix);
				*p++ = static_cast<char32>(digit < 10 ? (U'0' + digit) : (a + digit - 10));
				++length;
			} while (remaining > 0);

			--p;

			do
			{
				std::swap(*p, *first_digit);
				--p;
				++first_digit;
			} while (first_digit < p);

			return String(buffer, length);
		}
	}

	String ToString(const int8 value)
	{
		return detail::IntFormatter(static_cast<int32>(value)).str();
	}

	String ToString(const uint8 value)
	{
		return detail::IntFormatter(static_cast<uint32>(value)).str();
	}

	String ToString(const int16 value)
	{
		return detail::IntFormatter(static_cast<int32>(value)).str();
	}

	String ToString(const uint16 value)
	{
		return detail::IntFormatter(static_cast<uint32>(value)).str();
	}

	String ToString(const int32 value)
	{
		return detail::IntFormatter(value).str();
	}

	String ToString(const uint32 value)
	{
		return detail::IntFormatter(value).str();
	}

	String ToString(const long value)
	{
		if constexpr (sizeof(long) == sizeof(int32))
		{
			return detail::IntFormatter(static_cast<int32>(value)).str();
		}
		else
		{
			return detail::IntFormatter(static_cast<int64>(value)).str();
		}
	}

	String ToString(const unsigned long value)
	{
		if constexpr (sizeof(unsigned long) == sizeof(uint32))
		{
			return detail::IntFormatter(static_cast<uint32>(value)).str();
		}
		else
		{
			return detail::IntFormatter(static_cast<uint64>(value)).str();
		}
	}

	String ToString(const long long value)
	{
		return detail::IntFormatter(static_cast<int64>(value)).str();
	}

	String ToString(const unsigned long long value)
	{
		return detail::IntFormatter(static_cast<uint64>(value)).str();
	}


	String ToString(const char value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(static_cast<uint8>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const int8 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(static_cast<uint8>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const uint8 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(value, radix.value(), false, letterCase);
	}

	String ToString(const int16 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(static_cast<uint16>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const uint16 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(value, radix.value(), false, letterCase);
	}

	String ToString(const int32 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(static_cast<uint32>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const uint32 value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(value, radix.value(), false, letterCase);
	}

	String ToString(const long value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(static_cast<uint32>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const unsigned long value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(value, radix.value(), false, letterCase);
	}

	String ToString(const long long value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(static_cast<uint64>(value), radix.value(), (radix.value() == 10 && value < 0), letterCase);
	}

	String ToString(const unsigned long long value, Arg::radix_<uint32> radix, const LetterCase letterCase)
	{
		return detail::ItoW(value, radix.value(), false, letterCase);
	}
}
