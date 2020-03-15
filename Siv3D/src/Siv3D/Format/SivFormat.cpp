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

# include <Siv3D/Format.hpp>

namespace s3d
{
	void Formatter(FormatData& formatData, const FormatData::DecimalPlaces decimalPlace)
	{
		formatData.decimalPlaces = decimalPlace;
	}

	void Formatter(FormatData& formatData, const bool value)
	{
		formatData.string.append(value ? U"true"_sv : U"false"_sv);
	}





	void Formatter(FormatData& formatData, const char ch)
	{
		formatData.string.push_back(static_cast<char32>(ch));
	}

	void Formatter(FormatData& formatData, const char8_t ch)
	{
		formatData.string.push_back(static_cast<char32>(ch));
	}

	void Formatter(FormatData& formatData, const char16_t ch)
	{
		formatData.string.push_back(static_cast<char32>(ch));
	}

	void Formatter(FormatData& formatData, const wchar_t ch)
	{
		formatData.string.push_back(static_cast<char32>(ch));
	}

	void Formatter(FormatData& formatData, const char32_t ch)
	{
		formatData.string.push_back(static_cast<char32>(ch));
	}

	void Formatter(FormatData& formatData, std::nullptr_t)
	{
		formatData.string.append(U"null"_sv);
	}




	void Formatter(FormatData& formatData, const char32_t* s)
	{
		formatData.string.append(s);
	}

	void Formatter(FormatData& formatData, const StringView s)
	{
		formatData.string.append(s);
	}

	void Formatter(FormatData& formatData, const std::u32string& s)
	{
		formatData.string.append(s);
	}

	void Formatter(FormatData& formatData, const String& s)
	{
		formatData.string.append(s);
	}
}
