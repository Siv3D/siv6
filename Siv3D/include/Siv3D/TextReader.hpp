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

# pragma once
# include <memory>
# include "Common.hpp"
# include "TextEncoding.hpp"
# include "Optional.hpp"
# include "Unspecified.hpp"

namespace s3d
{
	/// @brief 読み込み用テキストファイル
	class TextReader
	{
	private:

		class TextReaderDetail;

		std::shared_ptr<TextReaderDetail> pImpl;

	public:

		TextReader();

		explicit TextReader(FilePathView path, const Optional<TextEncoding>& encoding = unspecified);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		explicit TextReader(Reader&& reader, const Optional<TextEncoding>& encoding = unspecified);

		explicit TextReader(const std::shared_ptr<IReader>& reader, const Optional<TextEncoding>& encoding = unspecified);

		~TextReader();

		bool open(FilePathView path, const Optional<TextEncoding>& encoding = unspecified);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool open(Reader&& reader, const Optional<TextEncoding>& encoding = unspecified);

		bool open(const std::shared_ptr<IReader>& reader, const Optional<TextEncoding>& encoding = unspecified);

		void close();

		[[nodiscard]]
		bool isOpen() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		Optional<char32> readChar();

		[[nodiscard]]
		Optional<String> readLine();

		[[nodiscard]]
		Array<String> readLines();

		[[nodiscard]]
		String readAll();

		bool readChar(char32& ch);

		bool readLine(String& line);

		bool readLines(Array<String>& lines);

		bool readAll(String& s);

		[[nodiscard]]
		TextEncoding encoding() const noexcept;

		[[nodiscard]]
		const FilePath& path() const noexcept;
	};
}

# include "detail/TextReader.ipp"
