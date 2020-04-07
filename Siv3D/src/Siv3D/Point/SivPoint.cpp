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

# include <Siv3D/Point.hpp>
# include <Siv3D/FormatInt.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const Point& value)
	{
		const size_t bufferSize = 12 * 2 + 5;
		char32 buf[bufferSize];
		char32* p = buf;

		*(p++) = U'(';
		detail::AppendInt(&p, value.x);
		*(p++) = U',';
		*(p++) = U' ';
		detail::AppendInt(&p, value.y);
		*(p++) = U')';

		formatData.string.append(buf, p - buf);
	}
}
