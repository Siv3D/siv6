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

# include <miniutf/miniutf.hpp>
# include <Siv3D/Unicode.hpp>
# include "UnicodeUtility.hpp"

namespace s3d
{
	namespace Unicode
	{
		String FromUTF8(const std::string_view s)
		{
			String result(detail::UTF32_Length(s), '0');

			const char8* pSrc = s.data();
			const char8* const pSrcEnd = pSrc + s.size();
			char32* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;
				*pDst++ = detail::utf8_decode(pSrc, pSrcEnd - pSrc, offset);
				pSrc += offset;
			}

			return result;
		}

		String FromUTF16(const std::u16string_view s)
		{
			String result(detail::UTF32_Length(s), '0');

			const char16* pSrc = s.data();
			const char16* const pSrcEnd = pSrc + s.size();
			char32* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;
				*pDst++ = detail::utf16_decode(pSrc, pSrcEnd - pSrc, offset);
				pSrc += offset;
			}

			return result;
		}

		String FromUTF32(const std::u32string_view s)
		{
			return String(s);
		}

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

		std::u32string ToUTF32(const StringView s)
		{
			return std::u32string(s.begin(), s.end());
		}
	}
}
