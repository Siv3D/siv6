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

# include <Siv3D/ParseInt.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <ThirdParty/abseil/numbers.hpp>

namespace s3d
{
	template <>
	int8 ParseInt<int8>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<int8>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<int8>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	uint8 ParseInt<uint8>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<uint8>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<uint8>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	int16 ParseInt<int16>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<int16>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<int16>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	uint16 ParseInt<uint16>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<uint16>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<uint16>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	int32 ParseInt<int32>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<int32>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<int32>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	uint32 ParseInt<uint32>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<uint32>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<uint32>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	long ParseInt<long>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<long>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<long>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	unsigned long ParseInt<unsigned long>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<unsigned long>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<unsigned long>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	long long ParseInt<long long>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<long long>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<long long>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	unsigned long long ParseInt<unsigned long long>(const StringView s, const Arg::radix_<uint32> radix)
	{
		if (const auto opt = ParseIntOpt<unsigned long long>(s, radix))
		{
			return *opt;
		}
		else
		{
			throw ParseError(U"ParseInt<unsigned long long>(\"{}\") failed"_fmt(s));
		}
	}

	template <>
	Optional<int8> ParseIntOpt<int8>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		int32 result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}
		else if (!InRange<int32>(result, INT8_MIN, INT8_MAX))
		{
			return none;
		}

		return static_cast<int8>(result);
	}

	template <>
	Optional<uint8> ParseIntOpt<uint8>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		uint32 result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}
		else if (UINT8_MAX < result)
		{
			return none;
		}

		return static_cast<uint8>(result);
	}

	template <>
	Optional<int16> ParseIntOpt<int16>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		int32 result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}
		else if (!InRange<int32>(result, INT16_MIN, INT16_MAX))
		{
			return none;
		}

		return static_cast<int16>(result);
	}

	template <>
	Optional<uint16> ParseIntOpt<uint16>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		uint32 result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}
		else if (UINT16_MAX < result)
		{
			return none;
		}

		return static_cast<uint16>(result);
	}

	template <>
	Optional<int32> ParseIntOpt<int32>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		int32 result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<uint32> ParseIntOpt<uint32>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		uint32 result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<long> ParseIntOpt<long>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		long result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<unsigned long> ParseIntOpt<unsigned long>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		unsigned long result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<long long> ParseIntOpt<long long>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		long long result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}

		return result;
	}

	template <>
	Optional<unsigned long long> ParseIntOpt<unsigned long long>(const StringView s, const Arg::radix_<uint32> radix) noexcept
	{
		unsigned long long result;

		if (!detail::safe_int_internal(s, &result, *radix))
		{
			return none;
		}

		return result;
	}
}
