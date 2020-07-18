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
# include "Common.hpp"

namespace s3d
{
	class INIData
	{
	public:

		using Section = String;

		using Name = String;

		using Value = String;

	private:


	public:

		INIData();

		explicit INIData(FilePathView path);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		explicit INIData(Reader&& reader, const Optional<TextEncoding>& encoding = unspecified);

		explicit INIData(const std::shared_ptr<IReader>& reader, const Optional<TextEncoding>& encoding = unspecified);

		bool load(FilePathView path);

		template <class Reader, std::enable_if_t<std::is_base_of_v<IReader, Reader> && !std::is_lvalue_reference_v<Reader>>* = nullptr>
		bool load(Reader&& reader, const Optional<TextEncoding>& encoding = unspecified);

		bool load(const std::shared_ptr<IReader>& reader, const Optional<TextEncoding>& encoding = unspecified);

		void clear();

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;
	};
}

# include "detail/INIData.ipp"
