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

# include <Siv3D/Unicode.hpp>
# include "UnicodeUtility.hpp"

namespace s3d
{
	namespace Unicode
	{
		std::string ToUTF8(const StringView s)
		{
			std::string result(detail::UTF8_Length(s), '0');

			const char32* pSrc = s.data();
			const char32* const pSrcEnd = pSrc + s.size();
			char8* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				detail::UTF8_Encode(&pDst, *pSrc++);
			}

			return result;
		}

		std::u16string ToUTF16(const StringView s)
		{
			std::u16string result(detail::UTF16_Length(s), u'0');

			const char32* pSrc = s.data();
			const char32* const pSrcEnd = pSrc + s.size();
			char16* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				detail::UTF16_Encode(&pDst, *pSrc++);
			}

			return result;
		}
	}
}
