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
# include <iostream>
# include <string>
# include "Platform.hpp"
# include "Types.hpp"
# include "Concepts.hpp"
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
		SIV3D_NODISCARD_CXX20
		String();

		/// <summary>
		/// 文字列をコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="other">
		/// コピーする文字列
		/// </param>
		SIV3D_NODISCARD_CXX20
		String(const String& other);

		/// <summary>
		/// 文字列をコピーして新しい文字列を作成します。
		/// </summary>
		/// <param name="s">
		/// コピーする文字列
		/// </param>
		SIV3D_NODISCARD_CXX20
		String(const string_type& s);

		SIV3D_NODISCARD_CXX20
		String(const String& other, size_type pos);

		SIV3D_NODISCARD_CXX20
		String(const String& other, size_type pos, size_type count);

		SIV3D_NODISCARD_CXX20
		String(const value_type* s);

		SIV3D_NODISCARD_CXX20
		String(const value_type* s, size_type count);

		SIV3D_NODISCARD_CXX20
		String(std::initializer_list<value_type> ilist);

		SIV3D_NODISCARD_CXX20
		String(size_t count, value_type ch);

		template <class Iterator>
		SIV3D_NODISCARD_CXX20
		String(Iterator first, Iterator last);

		SIV3D_NODISCARD_CXX20
		String(String&& other) noexcept;

		SIV3D_NODISCARD_CXX20
		String(string_type&& s) noexcept;

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		SIV3D_NODISCARD_CXX20
		explicit String(const StringViewIsh& s);

		operator StringView() const noexcept;

		String& operator =(const String& other);

		String& operator =(const string_type& text);

		String& operator =(String&& other) noexcept;

		String& operator =(string_type&& s) noexcept;

		String& operator =(const value_type* s);

		String& operator =(std::initializer_list<value_type> ilist);

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		String& operator =(const StringViewIsh& s);

		String& assign(const String& s);

		String& assign(const string_type& s);

		String& assign(const value_type* s);

		String& assign(size_t count, value_type ch);

		String& assign(String&& s) noexcept;

		String& assign(string_type&& s) noexcept;

		String& assign(std::initializer_list<value_type> ilist);

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		String& assign(const StringViewIsh& s);

		template <class Iterator>
		String& assign(Iterator first, Iterator last);

		String& operator <<(value_type ch);

		String& operator +=(const String& s);

		String& operator +=(const string_type& s);

		String& operator +=(value_type ch);

		String& operator +=(const value_type* s);

		String& operator +=(std::initializer_list<value_type> ilist);

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		String& operator +=(const StringViewIsh& s);

		String& append(const String& s);

		String& append(const string_type& s);

		String& append(value_type ch);

		String& append(const value_type* s);

		String& append(const value_type* s, size_t count);

		String& append(std::initializer_list<value_type> ilist);

		String& append(size_t count, value_type ch);

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		String& append(const StringViewIsh& s);

		template <class Iterator>
		String& append(Iterator first, Iterator last);

		String& insert(size_t offset, const String& s);

		String& insert(size_t offset, std::initializer_list<value_type> ilist);

		String& insert(size_t offset, const value_type* s);

		template <class StringViewIsh, class = IsStringViewIsh<StringViewIsh>>
		String& insert(size_t offset, const StringViewIsh& s);

		String& insert(size_t offset, size_t count, value_type ch);

		iterator insert(const_iterator where, value_type ch);

		iterator insert(const_iterator where, size_t count, value_type ch);

		template <class Iterator>
		iterator insert(const_iterator where, Iterator first, Iterator last);

		template <class Iterator>
		String& insert(const_iterator first1, const_iterator last1, Iterator first2, Iterator last2);

		String& erase(size_t offset = 0, size_t count = npos);

		iterator erase(const_iterator where) noexcept;

		iterator erase(const_iterator first, const_iterator last) noexcept;

		void clear() noexcept;

		[[nodiscard]]
		iterator begin() noexcept;

		[[nodiscard]]
		const_iterator begin() const noexcept;

		[[nodiscard]]
		const_iterator cbegin() const noexcept;

		[[nodiscard]]
		iterator end() noexcept;

		[[nodiscard]]
		const_iterator end() const noexcept;

		[[nodiscard]]
		const_iterator cend() const noexcept;

		[[nodiscard]]
		reverse_iterator rbegin() noexcept;

		[[nodiscard]]
		const_reverse_iterator rbegin() const noexcept;

		[[nodiscard]]
		const_reverse_iterator crbegin() const noexcept;

		[[nodiscard]]
		reverse_iterator rend() noexcept;

		[[nodiscard]]
		const_reverse_iterator rend() const noexcept;

		[[nodiscard]]
		const_reverse_iterator crend() const noexcept;

		void shrink_to_fit();

		void release();

		[[nodiscard]]
		value_type& at(size_t offset) &;

		[[nodiscard]]
		const value_type& at(size_t offset) const&;

		[[nodiscard]]
		value_type at(size_t offset) &&;

		[[nodiscard]]
		value_type& operator[](size_t offset) & noexcept;

		[[nodiscard]]
		const value_type& operator[](size_t offset) const& noexcept;

		[[nodiscard]]
		value_type operator[](size_t offset) && noexcept;

		void push_front(value_type ch);

		void push_back(value_type ch);

		void pop_front();

		void pop_back() noexcept;

		[[nodiscard]] value_type& front() noexcept;

		[[nodiscard]] const value_type& front() const noexcept;

		[[nodiscard]] value_type& back() noexcept;

		[[nodiscard]] const value_type& back() const noexcept;

		[[nodiscard]]
		const value_type* c_str() const noexcept;

		[[nodiscard]]
		const value_type* data() const noexcept;

		[[nodiscard]]
		value_type* data() noexcept;

		[[nodiscard]]
		string_type& str() noexcept;

		[[nodiscard]]
		const string_type& str() const noexcept;

		[[nodiscard]]
		size_t length() const noexcept;

		[[nodiscard]]
		size_t size() const noexcept;

		[[nodiscard]]
		size_t size_bytes() const noexcept;

		[[nodiscard]]
		bool empty() const noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		[[nodiscard]]
		size_t max_size() const noexcept;

		[[nodiscard]]
		size_t capacity() const noexcept;

		void resize(size_t newSize);

		void resize(size_t newSize, value_type ch);

		void reserve(size_t newCapacity);

		void swap(String& other) noexcept;

		[[nodiscard]]
		String substr(size_t offset = 0, size_t count = npos) const;

		[[nodiscard]]
		StringView substrView(size_t offset = 0, size_t count = npos) const &;

		[[nodiscard]]
		StringView substrView(size_t offset = 0, size_t count = npos) && = delete;

		/// <summary>
		/// 文字列をマルチバイト文字列に変換した結果を返します。
		/// </summary>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		std::string narrow() const;

		/// <summary>
		/// 文字列を std::wstring に変換した結果を返します。
		/// </summary>
		/// <returns>
		/// 変換された文字列
		/// </returns>
		[[nodiscard]]
		std::wstring toWstr() const;

		/// <summary>
		/// 文字列を UTF8 の std::string にエンコードします。
		/// </summary>
		/// <returns>
		/// UTF8 でエンコードされた std::string
		/// </returns>
		[[nodiscard]]
		std::string toUTF8() const;

		/// <summary>
		/// 文字列を UTF16 の std::u16string にエンコードします。
		/// </summary>
		/// <returns>
		/// UTF16 でエンコードされた std::u16string
		/// </returns>
		[[nodiscard]]
		std::u16string toUTF16() const;

		/// <summary>
		/// 文字列を UTF32 の std::u32string にエンコードします。
		/// </summary>
		/// <returns>
		/// UTF32 でエンコードされた std::u32string
		/// </returns>
		[[nodiscard]]
		const std::u32string& toUTF32() const noexcept;

		/// <summary>
		/// 文字列を指定した位置から検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="text">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t indexOf(const String& s, size_t offset = 0) const noexcept;

		/// <summary>
		/// 文字列を指定した位置から検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="text">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <remarks>
		/// text は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t indexOf(const value_type* s, size_t offset = 0) const noexcept;

		/// <summary>
		/// 文字を指定した位置から検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t indexOf(value_type ch, size_t offset = 0) const noexcept;

		/// <summary>
		/// 文字を指定した位置から検索し、最初にそれとは異なる文字が現れた位置を返します。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t indexOfNot(value_type ch, size_t offset = 0) const noexcept;

		/// <summary>
		/// 文字列を後方から逆順に検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="text">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t lastIndexOf(const String& text, size_t offset = npos) const noexcept;

		/// <summary>
		/// 文字列を後方から逆順に検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="text">
		/// 検索する文字列
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <remarks>
		/// text は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字列が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t lastIndexOf(const value_type* text, size_t offset = npos) const noexcept;

		/// <summary>
		/// 文字を後方から逆順に検索し、最初に現れた位置を返します。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t lastIndexOf(value_type ch, size_t offset = npos) const noexcept;

		/// <summary>
		/// 文字を後方から逆順に検索し、最初にそれとは異なる文字が現れた位置を返します。
		/// </summary>
		/// <param name="ch">
		/// 検索する文字
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t lastIndexNotOf(value_type ch, size_t offset = npos) const noexcept;

		/// <summary>
		/// 検索する文字のいずれかが最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t indexOfAny(const String& anyof, size_t offset = 0) const noexcept;

		/// <summary>
		/// 検索する文字のいずれかが最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <remarks>
		/// text は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t indexOfAny(const value_type* anyof, size_t offset = 0) const noexcept;

		/// <summary>
		/// 文字を後方から逆順に検索し、検索する文字のいずれかが最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t lastIndexOfAny(const String& anyof, size_t offset = npos) const noexcept;

		/// <summary>
		/// 文字を後方から逆順に検索し、検索する文字のいずれかが最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <remarks>
		/// anyof は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t lastIndexOfAny(const value_type* anyof, size_t offset = npos) const noexcept;

		/// <summary>
		/// 検索する文字に含まれない文字が最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t indexNotOfAny(const String& anyof, size_t offset = 0) const;

		/// <summary>
		/// 検索する文字に含まれない文字が最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置
		/// </param>
		/// <remarks>
		/// anyof は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t indexNotOfAny(const value_type* anyof, size_t offset = 0) const;

		/// <summary>
		/// 文字を後方から逆順に検索し、検索する文字に含まれない文字が最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t lastIndexNotOfAny(const String& anyof, size_t offset = npos) const;

		/// <summary>
		/// 文字を後方から逆順に検索し、検索する文字に含まれない文字が最初に現れた位置を返します。
		/// </summary>
		/// <param name="anyof">
		/// 検索する文字の集合
		/// </param>
		/// <param name="offset">
		/// 検索を開始する位置。npos の場合は終端から
		/// </param>
		/// <remarks>
		/// anyof は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 検索した文字とは異なる文字が最初に現れた位置。見つからなかった場合は npos
		/// </returns>
		[[nodiscard]]
		size_t lastIndexNotOfAny(const value_type* anyof, size_t offset = npos) const;

		/// <summary>
		/// 文字列の大小を比較します。
		/// </summary>
		/// <param name="text">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		[[nodiscard]]
		int32 compare(const String& text) const noexcept;

		/// <summary>
		/// 文字列の大小を比較します。
		/// </summary>
		/// <param name="text">
		/// 比較対象の文字列
		/// </param>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		[[nodiscard]]
		int32 compare(StringView view) const noexcept;

		/// <summary>
		/// 文字列の大小を比較します。
		/// </summary>
		/// <param name="text">
		/// 比較対象の文字列
		/// </param>
		/// <remarks>
		/// text は NULL 終端されている必要があります。
		/// </remarks>
		/// <returns>
		/// 比較結果。等しければ 0, 小さければ &lt;0, 大きければ &gt;0
		/// </returns>
		[[nodiscard]]
		int32 compare(const value_type* text) const noexcept;








		/// <summary>
		/// 文字列が等しいかを調べます。
		/// </summary>
		/// <param name="lhs">
		/// 比較する文字列
		/// </param>
		/// <param name="rhs">
		/// 比較する文字列
		/// </param>
		/// <returns>
		/// 等しければ true, それ以外の場合は false
		/// </returns>	
		[[nodiscard]]
		friend bool operator ==(const String& lhs, const String& rhs) noexcept
		{
			return (lhs.m_string == rhs.m_string);
		}

		[[nodiscard]]
		friend bool operator ==(const value_type* lhs, const String& rhs)
		{
			return (lhs == rhs.str());
		}

		[[nodiscard]]
		friend bool operator ==(const String& lhs, const value_type* rhs)
		{
			return (lhs.str() == rhs);
		}

		/// <summary>
		/// 文字列が等しくないかを調べます。
		/// </summary>
		/// <param name="lhs">
		/// 比較する文字列
		/// </param>
		/// <param name="rhs">
		/// 比較する文字列
		/// </param>
		/// <returns>
		/// 等しくなければ true, それ以外の場合は false
		/// </returns>
		[[nodiscard]]
		friend bool operator !=(const String& lhs, const String& rhs) noexcept
		{
			return (lhs.m_string != rhs.m_string);
		}

		[[nodiscard]]
		friend bool operator !=(const value_type* lhs, const String& rhs)
		{
			return (lhs != rhs.str());
		}

		[[nodiscard]]
		friend bool operator !=(const String& lhs, const value_type* rhs)
		{
			return (lhs.str() != rhs);
		}

		[[nodiscard]]
		friend bool operator <(const String& lhs, const String& rhs) noexcept
		{
			return (lhs.m_string < rhs.m_string);
		}

		[[nodiscard]]
		friend bool operator <(const value_type* lhs, const String& rhs)
		{
			return (lhs < rhs.str());
		}

		[[nodiscard]]
		friend bool operator <(const String& lhs, const value_type* rhs)
		{
			return (lhs.str() < rhs);
		}

		[[nodiscard]]
		friend bool operator >(const String& lhs, const String& rhs) noexcept
		{
			return (lhs.m_string > rhs.m_string);
		}

		[[nodiscard]]
		friend bool operator >(const value_type* lhs, const String& rhs)
		{
			return (lhs > rhs.str());
		}

		[[nodiscard]]
		friend bool operator >(const String& lhs, const value_type* rhs)
		{
			return (lhs.str() > rhs);
		}

		[[nodiscard]]
		friend bool operator <=(const String& lhs, const String& rhs) noexcept
		{
			return (lhs.m_string <= rhs.m_string);
		}

		[[nodiscard]]
		friend bool operator <=(const value_type* lhs, const String& rhs)
		{
			return (lhs <= rhs.str());
		}

		[[nodiscard]]
		friend bool operator <=(const String& lhs, const value_type* rhs)
		{
			return (lhs.str() <= rhs);
		}

		[[nodiscard]]
		friend bool operator >=(const String& lhs, const String& rhs) noexcept
		{
			return (lhs.m_string >= rhs.m_string);
		}

		[[nodiscard]]
		friend bool operator >=(const value_type* lhs, const String& rhs)
		{
			return (lhs >= rhs.str());
		}

		[[nodiscard]]
		friend bool operator >=(const String& lhs, const value_type* rhs)
		{
			return (lhs.str() >= rhs);
		}

		[[nodiscard]]
		friend String operator +(const value_type lhs, StringView rhs)
		{
			String result;
			result.reserve(1 + rhs.size());
			result.append(lhs);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const value_type lhs, const String& rhs)
		{
			String result;
			result.reserve(1 + rhs.size());
			result.append(lhs);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const value_type lhs, String&& rhs)
		{
			rhs.push_front(lhs);
			return std::move(rhs);
		}

		[[nodiscard]]
		friend String operator +(const value_type* lhs, StringView rhs)
		{
			const size_t len = std::char_traits<value_type>::length(lhs);
			String result;
			result.reserve(len + rhs.size());
			result.append(lhs, len);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const value_type* lhs, const String& rhs)
		{
			const size_t len = std::char_traits<value_type>::length(lhs);
			String result;
			result.reserve(len + rhs.size());
			result.append(lhs, len);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const value_type* lhs, String&& rhs)
		{
			return std::move(rhs.insert(0, lhs));
		}

		[[nodiscard]]
		friend String operator +(StringView lhs, const value_type rhs)
		{
			String result;
			result.reserve(lhs.size() + 1);
			result.append(lhs);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(StringView lhs, const value_type* rhs)
		{
			const size_t len = std::char_traits<value_type>::length(rhs);
			String result;
			result.reserve(lhs.size() + len);
			result.append(lhs);
			result.append(rhs, len);
			return result;
		}

		[[nodiscard]]
		friend String operator +(StringView lhs, StringView rhs)
		{
			String result;
			result.reserve(lhs.size() + rhs.size());
			result.append(lhs);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(StringView lhs, const String& rhs)
		{
			String result;
			result.reserve(lhs.size() + rhs.size());
			result.append(lhs);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(StringView lhs, String&& rhs)
		{
			return std::move(rhs.insert(0, lhs));
		}

		[[nodiscard]]
		friend String operator +(const String& lhs, const value_type rhs)
		{
			String result;
			result.reserve(lhs.size() + 1);
			result.append(lhs);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const String& lhs, const value_type* rhs)
		{
			const size_t len = std::char_traits<value_type>::length(rhs);
			String result;
			result.reserve(lhs.size() + len);
			result.append(lhs);
			result.append(rhs, len);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const String& lhs, StringView rhs)
		{
			String result;
			result.reserve(lhs.size() + rhs.size());
			result.append(lhs);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const String& lhs, const String& rhs)
		{
			String result;
			result.reserve(lhs.size() + rhs.size());
			result.append(lhs);
			result.append(rhs);
			return result;
		}

		[[nodiscard]]
		friend String operator +(const String& lhs, String&& rhs)
		{
			return std::move(rhs.insert(0, lhs));
		}

		[[nodiscard]]
		friend String operator +(String&& lhs, const value_type rhs)
		{
			return std::move(lhs << rhs);
		}

		[[nodiscard]]
		friend String operator +(String&& lhs, const value_type* rhs)
		{
			return std::move(lhs.append(rhs));
		}

		[[nodiscard]]
		friend String operator +(String&& lhs, StringView rhs)
		{
			return std::move(lhs.append(rhs));
		}

		[[nodiscard]]
		friend String operator +(String&& lhs, const String& rhs)
		{
			return std::move(lhs.append(rhs));
		}

		[[nodiscard]]
		friend String operator +(String&& lhs, String&& rhs)
		{
			if (rhs.size() <= lhs.capacity() - lhs.size() || rhs.capacity() - rhs.size() < lhs.size())
			{
				return std::move(lhs.append(rhs));
			}
			else
			{
				return std::move(rhs.insert(0, lhs));
			}
		}

		friend std::ostream& operator <<(std::ostream& output, const String& value)
		{
			return (output << value.narrow());
		}

		friend std::wostream& operator <<(std::wostream& output, const String& value)
		{
			return (output << value.toWstr());
		}
	};

	inline namespace Literals
	{
		inline namespace StringLiterals
		{
			[[nodiscard]]
			inline String operator ""_s(const char32_t* s, const size_t length)
			{
				return String(s, length);
			}
		}
	}

	using FilePath = String;
}

# include "String.ipp"
