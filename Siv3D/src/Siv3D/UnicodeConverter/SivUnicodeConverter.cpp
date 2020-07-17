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

# include <Siv3D/UnicodeConverter.hpp>
# include <ThirdParty/miniutf/miniutf.hpp>

namespace s3d
{
	bool UTF8toUTF32_Converter::put(const char8 code) noexcept
	{
		m_buffer[m_count++] = code;

		const auto result = detail::utf8_decode_check(m_buffer, m_count);

		if (result.offset != -1)
		{
			m_result = result.codePoint;

			m_count = 0;

			return true;
		}

		if (m_count >= 4)
		{
			m_result = 0xFFFD;

			m_count = 0;

			return true;
		}

		return false;
	}
}
