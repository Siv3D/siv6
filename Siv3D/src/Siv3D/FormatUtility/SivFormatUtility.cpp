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

# include <Siv3D/FormatUtility.hpp>
# include <Siv3D/FormatFloat.hpp>

namespace s3d
{
	namespace detail
	{
		static constexpr StringView bytesUnits[9] =
		{
			U"B"_sv,
			U"KiB"_sv,
			U"MiB"_sv,
			U"GiB"_sv,
			U"TiB"_sv,
			U"PiB"_sv,
			U"EiB"_sv,
			U"ZiB"_sv,
			U"YiB"_sv
		};
	}

	String FormatDataSize(const int64 bytes)
	{
		double s = static_cast<double>(bytes);

		for (uint32 i = 0; i < 9; ++i)
		{
			if (s < 10.0)
			{
				return ToString(s, 2) + detail::bytesUnits[i];
			}
			else if (s < 100.0)
			{
				return ToString(s, 1) + detail::bytesUnits[i];
			}
			else if (s < 1024.0)
			{
				return ToString(s, 0) + detail::bytesUnits[i];
			}

			s /= 1024.0;
		}

		return String();
	}
}
