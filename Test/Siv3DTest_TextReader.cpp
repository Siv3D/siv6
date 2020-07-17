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

# define CATCH_CONFIG_FAST_COMPILE
# define CATCH_CONFIG_ENABLE_BENCHMARKING
# include <ThirdParty/Catch2/catch.hpp>

# include <Siv3D.hpp>
using namespace s3d;
using namespace std::literals;

TEST_CASE("TextReader")
{
	SECTION("Empty")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/empty.txt");
		const TextReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(reader.encoding() == TextEncoding::Default);
		REQUIRE(reader.path() == path);
	}

	SECTION("UTF8_NO_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_no_bom.txt");
		const TextReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(reader.encoding() == TextEncoding::UTF8_NO_BOM);
		REQUIRE(reader.path() == path);
	}

	SECTION("UTF8_WITH_BOM")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_with_bom.txt");
		const TextReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(reader.encoding() == TextEncoding::UTF8_WITH_BOM);
		REQUIRE(reader.path() == path);
	}

	SECTION("UTF16LE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_le.txt");
		const TextReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(reader.encoding() == TextEncoding::UTF16LE);
		REQUIRE(reader.path() == path);
	}

	SECTION("UTF16BE")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_be.txt");
		const TextReader reader(path);
		REQUIRE(reader.isOpen() == true);
		REQUIRE(reader.encoding() == TextEncoding::UTF16BE);
		REQUIRE(reader.path() == path);
	}
}


TEST_CASE("TextReader::readChar()")
{
	SECTION("Empty -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/empty.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF8_NO_BOM -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_no_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'S');
		REQUIRE(reader.readChar() == U'i');
		REQUIRE(reader.readChar() == U'v');
		REQUIRE(reader.readChar() == U'3');
		REQUIRE(reader.readChar() == U'D');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF8_WITH_BOM -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_with_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'S');
		REQUIRE(reader.readChar() == U'i');
		REQUIRE(reader.readChar() == U'v');
		REQUIRE(reader.readChar() == U'3');
		REQUIRE(reader.readChar() == U'D');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF16LE -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_le.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'S');
		REQUIRE(reader.readChar() == U'i');
		REQUIRE(reader.readChar() == U'v');
		REQUIRE(reader.readChar() == U'3');
		REQUIRE(reader.readChar() == U'D');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF16BE -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_be.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'S');
		REQUIRE(reader.readChar() == U'i');
		REQUIRE(reader.readChar() == U'v');
		REQUIRE(reader.readChar() == U'3');
		REQUIRE(reader.readChar() == U'D');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF8_NO_BOM -long")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_no_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'あ');
		REQUIRE(reader.readChar() == U'い');
		REQUIRE(reader.readChar() == U'う');
		REQUIRE(reader.readChar() == U'え');
		REQUIRE(reader.readChar() == U'お');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'𩸽');
		REQUIRE(reader.readChar() == U'齟');
		REQUIRE(reader.readChar() == U'齬');
		REQUIRE(reader.readChar() == U'😎');
		REQUIRE(reader.readChar() == U'🙊');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'C');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF8_WITH_BOM -long")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_with_bom.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'あ');
		REQUIRE(reader.readChar() == U'い');
		REQUIRE(reader.readChar() == U'う');
		REQUIRE(reader.readChar() == U'え');
		REQUIRE(reader.readChar() == U'お');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'𩸽');
		REQUIRE(reader.readChar() == U'齟');
		REQUIRE(reader.readChar() == U'齬');
		REQUIRE(reader.readChar() == U'😎');
		REQUIRE(reader.readChar() == U'🙊');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'C');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF16LE -long")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_le.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'あ');
		REQUIRE(reader.readChar() == U'い');
		REQUIRE(reader.readChar() == U'う');
		REQUIRE(reader.readChar() == U'え');
		REQUIRE(reader.readChar() == U'お');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'𩸽');
		REQUIRE(reader.readChar() == U'齟');
		REQUIRE(reader.readChar() == U'齬');
		REQUIRE(reader.readChar() == U'😎');
		REQUIRE(reader.readChar() == U'🙊');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'C');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}

	SECTION("UTF16BE -long")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_be.txt");
		TextReader reader(path);
		REQUIRE(reader.readChar() == U'あ');
		REQUIRE(reader.readChar() == U'い');
		REQUIRE(reader.readChar() == U'う');
		REQUIRE(reader.readChar() == U'え');
		REQUIRE(reader.readChar() == U'お');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'𩸽');
		REQUIRE(reader.readChar() == U'齟');
		REQUIRE(reader.readChar() == U'齬');
		REQUIRE(reader.readChar() == U'😎');
		REQUIRE(reader.readChar() == U'🙊');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'C');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'B');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'A');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == U'\n');
		REQUIRE(reader.readChar() == none);
		REQUIRE(reader.readChar() == none);
	}
}

TEST_CASE("TextReader::readChar(char32&)")
{
	SECTION("Empty -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/empty.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("UTF8_NO_BOM -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_no_bom.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'S');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'i');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'v');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'3');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'D');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("UTF8_WITH_BOM -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_with_bom.txt");
		TextReader reader(path);
	}

	SECTION("UTF16LE -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_le.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'S');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'i');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'v');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'3');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'D');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("UTF16BE -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_be.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'S');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'i');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'v');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'3');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'D');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("UTF8_NO_BOM -long")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_no_bom.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'あ');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'い');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'う');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'え');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'お');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'𩸽');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齟');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齬');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'😎');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'🙊');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'C');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("UTF8_WITH_BOM -long")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_with_bom.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'あ');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'い');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'う');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'え');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'お');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'𩸽');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齟');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齬');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'😎');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'🙊');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'C');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("UTF16LE -long")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_le.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'あ');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'い');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'う');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'え');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'お');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'𩸽');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齟');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齬');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'😎');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'🙊');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'C');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}

	SECTION("UTF16BE -long")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_be.txt");
		TextReader reader(path);
		char32 c = U'\0';
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'あ');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'い');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'う');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'え');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'お');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'𩸽');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齟');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'齬');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'😎');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'🙊');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'C');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'B');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'A');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == true);
		REQUIRE(c == U'\n');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
		REQUIRE(reader.readChar(c) == false);
		REQUIRE(c == U'\0');
	}
}

TEST_CASE("TextReader::readLine()")
{
	SECTION("Empty -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/empty.txt");
		TextReader reader(path);
		REQUIRE(reader.readLine() == none);
		REQUIRE(reader.readLine() == none);
	}

	SECTION("UTF8_NO_BOM -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_no_bom.txt");
		TextReader reader(path);
		//REQUIRE(reader.readLine() == U"Siv3D");
		//REQUIRE(reader.readLine() == none);
		//REQUIRE(reader.readLine() == none);
	}

	SECTION("UTF8_WITH_BOM -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf8_with_bom.txt");
		TextReader reader(path);
		//REQUIRE(reader.readLine() == U"Siv3D");
		//REQUIRE(reader.readLine() == none);
		//REQUIRE(reader.readLine() == none);
	}

	SECTION("UTF16LE -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_le.txt");
		TextReader reader(path);
		//REQUIRE(reader.readLine() == U"Siv3D");
		//REQUIRE(reader.readLine() == none);
		//REQUIRE(reader.readLine() == none);
	}

	SECTION("UTF16BE -short")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/utf16_be.txt");
		TextReader reader(path);
		//REQUIRE(reader.readLine() == U"Siv3D");
		//REQUIRE(reader.readLine() == none);
		//REQUIRE(reader.readLine() == none);
	}

	SECTION("UTF8_NO_BOM -long")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_no_bom.txt");
		TextReader reader(path);
	}

	SECTION("UTF8_WITH_BOM -long")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf8_with_bom.txt");
		TextReader reader(path);
	}

	SECTION("UTF16LE -long")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_le.txt");
		TextReader reader(path);
	}

	SECTION("UTF16BE -long")
	{
		const FilePath path = FileSystem::FullPath(U"test/text/long/utf16_be.txt");
		TextReader reader(path);
	}
}
