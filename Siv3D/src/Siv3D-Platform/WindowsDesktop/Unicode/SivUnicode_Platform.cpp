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
# include <Siv3D/Windows/Windows.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/Unicode/UnicodeUtility.hpp>

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		static std::string ToMultiByte(const std::wstring_view s, const uint32 codePage)
		{
			if (s.empty())
			{
				return std::string();
			}

			const int32 requiredSize = ::WideCharToMultiByte(codePage, 0,
				s.data(), static_cast<int>(s.length()),
				nullptr, 0, nullptr, nullptr);

			std::string result(requiredSize, '\0');

			::WideCharToMultiByte(codePage, 0,
				s.data(), static_cast<int>(s.length()),
				&result[0], requiredSize, nullptr, nullptr);

			return result;
		}
	}

	namespace Unicode
	{
		String FromWString(const std::wstring_view view)
		{
			const char16* pSrc = static_cast<const char16*>(static_cast<const void*>(view.data()));
			const char16* const pSrcEnd = pSrc + view.size();

			String result(detail::UTF32_Length(std::u16string_view(pSrc, view.size())), '0');
			char32* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				int32 offset;
				*pDst++ = detail::utf16_decode(pSrc, pSrcEnd - pSrc, offset);
				pSrc += offset;
			}

			return result;
		}

		std::string Narrow(const StringView s)
		{
			return detail::ToMultiByte(ToWstring(s), CP_ACP);
		}

		std::wstring ToWstring(const StringView s)
		{
			std::wstring result(detail::UTF16_Length(s), L'0');

			const char32* pSrc = s.data();
			const char32* const pSrcEnd = pSrc + s.size();
			wchar_t* pDst = &result[0];

			while (pSrc != pSrcEnd)
			{
				detail::UTF16_Encode(&pDst, *pSrc++);
			}

			return result;
		}
	}
}
