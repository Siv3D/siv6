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
# include <string>
# include "Types.hpp"
# include "StringView.hpp"

namespace s3d
{
	class String
	{
	public:
		
		using string_type				= std::u32string;
		using traits_type				= typename string_type::traits_type;
		using allocator_type			= typename string_type::allocator_type;
		using value_type				= typename string_type::value_type;
		using size_type					= typename string_type::size_type;
		using difference_type			= typename string_type::difference_type;
		using pointer					= typename string_type::pointer;
		using const_pointer				= typename string_type::const_pointer;
		using reference					= typename string_type::reference;
		using const_reference			= typename string_type::const_reference;
		using iterator					= typename string_type::iterator;
		using const_iterator			= typename string_type::const_iterator;
		using reverse_iterator			= typename string_type::reverse_iterator;
		using const_reverse_iterator	= typename string_type::const_reverse_iterator;

	private:

		string_type m_string;

	public:

		template <class StringViewIsh>
		using IsStringViewIsh = std::enable_if_t<
			std::conjunction_v<std::is_convertible<const StringViewIsh&, StringView>,
			std::negation<std::is_convertible<const StringViewIsh&, const char32*>>>>;

		static constexpr size_type npos{ static_cast<size_type>(-1) };
		
		/// <summary>
		/// default constructor
		/// </summary>
		String();

		/// <summary>
		/// 文字列をコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="other">
		/// コピーする文字列
		/// </param>
		String(const String& other);

		/// <summary>
		/// 文字列をコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="text">
		/// コピーする文字列
		/// </param>
		String(const string_type& s);

		String(const String& other, size_type pos);

		String(const String& other, size_type pos, size_type count);

		String(const value_type* s);

		String(const value_type* s, size_type count);

		String(std::initializer_list<value_type> ilist);

		String(size_t count, value_type ch);

		template <class Iterator>
		String(Iterator first, Iterator last);

		String(String&& other) noexcept;

		String(string_type&& s) noexcept;

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		explicit String(const StringViewIsh& viewish);
	};
}

# include "String.ipp"
