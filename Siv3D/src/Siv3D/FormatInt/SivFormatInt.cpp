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

# include <Siv3D/FormatInt.hpp>
# include <Siv3D/String.hpp>
# include <Siv3D/IntFormatter.hpp>

namespace s3d
{
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
}

