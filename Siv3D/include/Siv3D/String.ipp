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
	inline String::String(const StringViewIsh& viewish)
		: m_string(viewish.data(), viewish.size())
	{
	
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
}
