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

namespace s3d
{
	inline String::String()
		: m_string()
	{

	}

	inline String::String(const String& other)
		: m_string(other.m_string)
	{

	}

	inline String::String(const string_type& s)
		: m_string(s)
	{

	}

	inline String::String(const String& other, const size_type pos)
		: m_string(other.m_string, pos)
	{

	}

	inline String::String(const String& other, const size_type pos, const size_type count)
		: m_string(other.m_string, pos, count)
	{

	}

	inline String::String(const value_type* s)
		: m_string(s)
	{

	}

	inline String::String(const value_type* s, const size_type count)
		: m_string(s, count)
	{

	}

	inline String::String(std::initializer_list<value_type> ilist)
		: m_string(ilist)
	{

	}

	inline String::String(const size_t count, const value_type ch)
		: m_string(count, ch)
	{

	}

	template <class Iterator>
	inline String::String(Iterator first, Iterator last)
		: m_string(first, last)
	{
	
	}

	inline String::String(String&& other) noexcept
		: m_string(std::move(other.m_string))
	{

	}

	inline String::String(string_type&& s) noexcept
		: m_string(std::move(s))
	{

	}

	template <class StringViewIsh, class>
	inline String::String(const StringViewIsh& s)
		: m_string(s.data(), s.size())
	{
	
	}

	inline String::operator StringView() const noexcept
	{
		return StringView(m_string.data(), m_string.size());
	}

	inline String& String::operator =(const String& other)
	{
		return assign(other);
	}

	inline String& String::operator =(const string_type& s)
	{
		return assign(s);
	}

	inline String& String::operator =(String&& other) noexcept
	{
		return assign(std::move(other));
	}

	inline String& String::operator =(string_type&& s) noexcept
	{
		return assign(std::move(s));
	}

	inline String& String::operator =(const value_type* s)
	{
		return assign(s);
	}

	inline String& String::operator =(std::initializer_list<value_type> ilist)
	{
		return assign(ilist);
	}

	template <class StringViewIsh, class>
	inline String& String::operator =(const StringViewIsh& s)
	{
		return assign(s);
	}

	inline String& String::assign(const String& s)
	{
		m_string.assign(s.m_string);

		return *this;
	}

	inline String& String::assign(const string_type& s)
	{
		m_string.assign(s);

		return *this;
	}

	inline String& String::assign(const value_type* s)
	{
		m_string.assign(s);

		return *this;
	}

	inline String& String::assign(const size_t count, const value_type ch)
	{
		m_string.assign(count, ch);

		return *this;
	}

	inline String& String::assign(String&& s) noexcept
	{
		m_string.assign(std::move(s.m_string));

		return *this;
	}

	inline String& String::assign(string_type&& s) noexcept
	{
		m_string.assign(std::move(s));

		return *this;
	}

	inline String& String::assign(std::initializer_list<value_type> ilist)
	{
		m_string.assign(ilist);

		return *this;
	}

	template <class StringViewIsh, class>
	inline String& String::assign(const StringViewIsh& s)
	{
		m_string.assign(s.data(), s.size());

		return *this;
	}

	template <class Iterator>
	inline String& String::assign(Iterator first, Iterator last)
	{
		m_string.assign(first, last);

		return *this;
	}

	inline String::allocator_type String::get_allocator() const
	{
		return m_string.get_allocator();
	}

	inline String& String::operator <<(const value_type ch)
	{
		return append(ch);
	}

	inline String& String::operator +=(const String& s)
	{
		return append(s);
	}

	inline String& String::operator +=(const string_type& s)
	{
		return append(s);
	}

	inline String& String::operator +=(const value_type ch)
	{
		return append(ch);
	}

	inline String& String::operator +=(const value_type* s)
	{
		return append(s);
	}

	inline String& String::operator +=(std::initializer_list<value_type> ilist)
	{
		return append(ilist);
	}

	template <class StringViewIsh, class>
	inline String& String::operator +=(const StringViewIsh& s)
	{
		return append(s);
	}

	inline String& String::append(const String& s)
	{
		m_string.append(s.m_string);

		return *this;
	}

	inline String& String::append(const string_type& s)
	{
		m_string.append(s);

		return *this;
	}

	inline String& String::append(const value_type ch)
	{
		m_string.push_back(ch);

		return *this;
	}

	inline String& String::append(const value_type* s)
	{
		m_string.append(s);

		return *this;
	}

	inline String& String::append(const value_type* s, const size_t count)
	{
		m_string.append(s, count);

		return *this;
	}

	inline String& String::append(std::initializer_list<value_type> ilist)
	{
		m_string.append(ilist);

		return *this;
	}

	inline String& String::append(const size_t count, const value_type ch)
	{
		m_string.append(count, ch);

		return *this;
	}

	template <class StringViewIsh, class>
	inline String& String::append(const StringViewIsh& s)
	{
		m_string.append(s.data(), s.size());

		return *this;
	}

	template <class Iterator>
	inline String& String::append(Iterator first, Iterator last)
	{
		m_string.append(first, last);

		return *this;
	}

	inline String& String::insert(const size_t offset, const String& s)
	{
		m_string.insert(offset, s.m_string);

		return *this;
	}

	inline String& String::insert(const size_t offset, std::initializer_list<value_type> ilist)
	{
		m_string.insert(offset, ilist);

		return *this;
	}

	inline String& String::insert(const size_t offset, const value_type* s)
	{
		m_string.insert(offset, s);

		return *this;
	}

	template <class StringViewIsh, class>
	inline String& String::insert(const size_t offset, const StringViewIsh& s)
	{
		m_string.insert(offset, s.data(), s.size());

		return *this;
	}

	inline String& String::insert(const size_t offset, const size_t count, const value_type ch)
	{
		m_string.insert(offset, count, ch);

		return *this;
	}

	inline String::iterator String::insert(const_iterator where, const value_type ch)
	{
		return m_string.insert(where, ch);
	}

	inline String::iterator String::insert(const_iterator where, const size_t count, const value_type ch)
	{
		return m_string.insert(where, count, ch);
	}

	template <class Iterator>
	inline String::iterator String::insert(const_iterator where, Iterator first, Iterator last)
	{
		return m_string.insert(where, first, last);
	}

	template <class Iterator>
	inline String& String::insert(const_iterator first1, const_iterator last1, Iterator first2, Iterator last2)
	{
		m_string.insert(first1, last1, first2, last2);

		return *this;
	}

	inline String& String::erase(const size_t offset, const size_t count)
	{
		m_string.erase(offset, count);

		return *this;
	}

	inline String::iterator String::erase(const_iterator where) noexcept
	{
		return m_string.erase(where);
	}

	inline String::iterator String::erase(const_iterator first, const_iterator last) noexcept
	{
		return m_string.erase(first, last);
	}

	inline void String::clear() noexcept
	{
		m_string.clear();
	}

	inline String::iterator String::begin() noexcept
	{
		return m_string.begin();
	}

	inline String::const_iterator String::begin() const noexcept
	{
		return m_string.begin();
	}

	inline String::const_iterator String::cbegin() const noexcept
	{
		return m_string.cbegin();
	}

	inline String::iterator String::end() noexcept
	{
		return m_string.end();
	}

	inline String::const_iterator String::end() const noexcept
	{
		return m_string.end();
	}

	inline String::const_iterator String::cend() const noexcept
	{
		return m_string.cend();
	}

	inline String::reverse_iterator String::rbegin() noexcept
	{
		return m_string.rbegin();
	}

	inline String::const_reverse_iterator String::rbegin() const noexcept
	{
		return m_string.rbegin();
	}

	inline String::const_reverse_iterator String::crbegin() const noexcept
	{
		return m_string.crbegin();
	}

	inline String::reverse_iterator String::rend() noexcept
	{
		return m_string.rend();
	}

	inline String::const_reverse_iterator String::rend() const noexcept
	{
		return m_string.rend();
	}

	inline String::const_reverse_iterator String::crend() const noexcept
	{
		return m_string.crend();
	}

	inline void String::shrink_to_fit()
	{
		m_string.shrink_to_fit();
	}

	inline void String::release()
	{
		clear();

		shrink_to_fit();
	}

	inline String::value_type& String::at(const size_t offset)&
	{
		return m_string.at(offset);
	}

	inline const String::value_type& String::at(const size_t offset) const&
	{
		return m_string.at(offset);
	}

	inline String::value_type String::at(const size_t offset)&&
	{
		return m_string.at(offset);
	}

	inline String::value_type& String::operator[](const size_t offset)& noexcept
	{
		return m_string[offset];
	}

	inline const String::value_type& String::operator[](const size_t offset) const& noexcept
	{
		return m_string[offset];
	}

	inline String::value_type String::operator[](const size_t offset) && noexcept
	{
		return std::move(m_string[offset]);
	}

	inline void String::push_front(const value_type ch)
	{
		insert(begin(), ch);
	}

	inline void String::push_back(const value_type ch)
	{
		m_string.push_back(ch);
	}

	inline void String::pop_front()
	{
		m_string.erase(m_string.begin());
	}

	inline void String::pop_back() noexcept
	{
		m_string.pop_back();
	}

	inline String::value_type& String::front() noexcept
	{
		return m_string.front();
	}

	inline const String::value_type& String::front() const noexcept
	{
		return m_string.front();
	}

	inline String::value_type& String::back() noexcept
	{
		return m_string.back();
	}

	inline const String::value_type& String::back() const noexcept
	{
		return m_string.back();
	}

	inline const String::value_type* String::c_str() const noexcept
	{
		return m_string.c_str();
	}

	inline const String::value_type* String::data() const noexcept
	{
		return m_string.data();
	}

	inline String::value_type* String::data() noexcept
	{
		return m_string.data();
	}

	inline String::string_type& String::str() noexcept
	{
		return m_string;
	}

	inline const String::string_type& String::str() const noexcept
	{
		return m_string;
	}

	inline size_t String::length() const noexcept
	{
		return m_string.length();
	}

	inline size_t String::size() const noexcept
	{
		return m_string.size();
	}

	inline size_t String::size_bytes() const noexcept
	{
		return (m_string.size() * sizeof(value_type));
	}

	inline bool String::empty() const noexcept
	{
		return m_string.empty();
	}

	inline bool String::isEmpty() const noexcept
	{
		return m_string.empty();
	}

	inline String::operator bool() const noexcept
	{
		return not m_string.empty();
	}

	inline size_t String::max_size() const noexcept
	{
		return m_string.max_size();
	}

	inline size_t String::capacity() const noexcept
	{
		return m_string.capacity();
	}

	inline void String::resize(const size_t newSize)
	{
		m_string.resize(newSize);
	}

	inline void String::resize(const size_t newSize, const value_type ch)
	{
		m_string.resize(newSize, ch);
	}

	inline void String::reserve(const size_t newCapacity)
	{
		m_string.reserve(newCapacity);
	}

	inline void String::swap(String& other) noexcept
	{
		m_string.swap(other.m_string);
	}

	inline String String::substr(const size_t offset, const size_t count) const
	{
		return m_string.substr(offset, count);
	}

	inline StringView String::substrView(const size_t offset, const size_t count) const &
	{
		if (offset > size())
		{
			throw std::out_of_range("String::substrView() index out of range");
		}

		return StringView(data() + offset, std::min(count, size() - offset));
	}

	inline size_t String::indexOf(const String& s, const size_t offset) const noexcept
	{
		return m_string.find(s.data(), offset, s.length());
	}

	inline size_t String::indexOf(const value_type* s, const size_t offset) const noexcept
	{
		return m_string.find(s, offset, traits_type::length(s));
	}

	inline size_t String::indexOf(const value_type ch, const size_t offset) const noexcept
	{
		return m_string.find(ch, offset);
	}

	inline size_t String::indexOfNot(const value_type ch, const size_t offset) const noexcept
	{
		return m_string.find_first_not_of(ch, offset);
	}

	inline size_t String::lastIndexOf(const String& s, const size_t offset) const noexcept
	{
		return m_string.rfind(s.data(), offset, s.length());
	}

	inline size_t String::lastIndexOf(const value_type* s, const size_t offset) const noexcept
	{
		return m_string.rfind(s, offset, traits_type::length(s));
	}

	inline size_t String::lastIndexOf(const value_type ch, const size_t offset) const noexcept
	{
		return m_string.rfind(ch, offset);
	}

	inline size_t String::lastIndexNotOf(const value_type ch, const size_t offset) const noexcept
	{
		return m_string.find_last_not_of(ch, offset);
	}

	inline size_t String::indexOfAny(const String& anyof, const size_t offset) const noexcept
	{
		return m_string.find_first_of(anyof.data(), offset, anyof.length());
	}

	inline size_t String::indexOfAny(const value_type* anyof, const size_t offset) const noexcept
	{
		return m_string.find_first_of(anyof, offset, traits_type::length(anyof));
	}

	inline size_t String::lastIndexOfAny(const String& anyof, const size_t offset) const noexcept
	{
		return m_string.find_last_of(anyof.data(), offset, anyof.length());
	}

	inline size_t String::lastIndexOfAny(const value_type* anyof, const size_t offset) const noexcept
	{
		return m_string.find_last_of(anyof, offset, traits_type::length(anyof));
	}

	inline size_t String::indexNotOfAny(const String& anyof, const size_t offset) const
	{
		return m_string.find_first_not_of(anyof.data(), offset, anyof.length());
	}

	inline size_t String::indexNotOfAny(const value_type* anyof, const size_t offset) const
	{
		return m_string.find_first_not_of(anyof, offset, traits_type::length(anyof));
	}

	inline size_t String::lastIndexNotOfAny(const String& anyof, const size_t offset) const
	{
		return m_string.find_last_not_of(anyof.data(), offset, anyof.length());
	}

	inline size_t String::lastIndexNotOfAny(const value_type* anyof, const size_t offset) const
	{
		return m_string.find_last_not_of(anyof, offset, traits_type::length(anyof));
	}

	inline int32 String::compare(const String& s) const noexcept
	{
		return m_string.compare(s.m_string);
	}

	inline int32 String::compare(const StringView s) const noexcept
	{
		return m_string.compare(std::u32string_view(s.data(), s.size()));
	}

	inline int32 String::compare(const value_type* s) const noexcept
	{
		return m_string.compare(s);
	}

	inline void swap(String& a, String& b) noexcept
	{
		a.swap(b);
	}

	inline namespace Literals
	{
		inline namespace StringLiterals
		{
			inline String operator ""_s(const char32_t* s, const size_t length)
			{
				return String(s, length);
			}
		}
	}
}
