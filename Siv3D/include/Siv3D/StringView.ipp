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
# include <cassert>
# include <stdexcept>
# include <algorithm>

namespace s3d
{
	inline StringView::StringView(const std::u32string& s) noexcept
		: m_view(s)
	{
	
	}

	inline constexpr StringView::StringView(const std::u32string_view s) noexcept
		: m_view(s)
	{
	
	}

	inline constexpr StringView::StringView(const value_type* s, const size_type length) noexcept
		: m_view(s, length)
	{
	
	}

	inline constexpr StringView::StringView(const value_type* s) noexcept
		: m_view(s)
	{
	
	}

	inline constexpr StringView::const_iterator StringView::begin() const noexcept
	{
		return m_view.begin();
	}

	inline constexpr StringView::const_iterator StringView::end() const noexcept
	{
		return m_view.end();
	}

	inline constexpr StringView::const_iterator StringView::cbegin() const noexcept
	{
		return m_view.cbegin();
	}

	inline constexpr StringView::const_iterator StringView::cend() const noexcept
	{
		return m_view.cend();
	}

	inline constexpr StringView::const_reverse_iterator StringView::rbegin() const noexcept
	{
		return m_view.rbegin();
	}

	inline constexpr StringView::const_reverse_iterator StringView::rend() const noexcept
	{
		return m_view.rend();
	}

	inline constexpr StringView::const_reverse_iterator StringView::crbegin() const noexcept
	{
		return m_view.crbegin();
	}

	inline constexpr StringView::const_reverse_iterator StringView::crend() const noexcept
	{
		return m_view.crend();
	}

	inline constexpr StringView::const_reference StringView::operator[](const size_type index) const
	{
		return m_view[index];
	}

	inline constexpr StringView::const_reference StringView::at(const size_type index) const
	{
		if (index >= m_view.size())
		{
			throw std::out_of_range("StringView::at() index out of range");
		}

		return m_view[index];
	}

	inline constexpr StringView::const_reference StringView::front() const
	{
		assert(not empty() && "cannot call StringView::front() on empty StringView");

		return m_view[0];
	}

	inline constexpr StringView::const_reference StringView::back() const
	{
		assert(not empty() && "cannot call StringView::back() on empty StringView");

		return m_view[m_view.length() - 1];
	}

	inline constexpr StringView::const_pointer StringView::data() const noexcept
	{
		return m_view.data();
	}

	inline constexpr StringView::size_type StringView::size() const noexcept
	{
		return m_view.size();
	}

	inline constexpr StringView::size_type StringView::size_bytes() const noexcept
	{
		return (m_view.size() * sizeof(value_type));
	}

	inline constexpr StringView::size_type StringView::length() const noexcept
	{
		return m_view.length();
	}

	inline constexpr StringView::size_type StringView::max_size() const noexcept
	{
		return std::numeric_limits<size_type>::max();
	}

	inline constexpr bool StringView::empty() const noexcept
	{
		return m_view.empty();;
	}

	inline constexpr bool StringView::isEmpty() const noexcept
	{
		return m_view.empty();
	}

	inline constexpr StringView::operator bool() const noexcept
	{
		return not m_view.empty();
	}

	constexpr void StringView::remove_prefix(const size_type n) noexcept
	{
		m_view.remove_prefix(n);
	}

	inline constexpr void StringView::remove_suffix(const size_type n) noexcept
	{
		m_view.remove_suffix(n);
	}

	inline constexpr void StringView::swap(StringView& other) noexcept
	{
		m_view.swap(other.m_view);
	}

	inline constexpr void StringView::clear() noexcept
	{
		*this = StringView();
	}

#if defined(__GNUC__) && !defined(__clang__)
	inline StringView::size_type StringView::copy(value_type* dst, const size_type n, const size_type pos) const
#else
	inline constexpr StringView::size_type StringView::copy(value_type* dst, const size_type n, const size_type pos) const
#endif
	{
		return m_view.copy(dst, n, pos);
	}

	inline constexpr StringView StringView::substr(const size_type pos, const size_type n) const
	{
		if (pos > m_view.size())
		{
			throw std::out_of_range("StringView::substr()");
		}

		return StringView(m_view.data() + pos, std::min(n, m_view.size() - pos));
	}

	inline constexpr int32 StringView::compare(const StringView sv) const noexcept
	{
		return m_view.compare(sv.m_view);
	}

	inline constexpr int32 StringView::compare(const size_type pos1, const size_type n1, const StringView sv) const noexcept
	{
		return m_view.compare(pos1, n1, sv.m_view);
	}

	inline constexpr int32 StringView::compare(const size_type pos1, const size_type n1, const StringView sv, const size_type pos2, const size_type n2) const noexcept
	{
		return m_view.compare(pos1, n1, sv.m_view, pos2, n2);
	}

	inline constexpr int32 StringView::compare(const value_type* str) const noexcept
	{
		return m_view.compare(str);
	}

	inline constexpr int32 StringView::compare(const size_type pos1, const size_type n1, const value_type* str) const noexcept
	{
		return m_view.compare(pos1, n1, str);
	}

	inline constexpr int32 StringView::compare(const size_type pos1, const size_type n1, const value_type* str, const size_type n2) const noexcept
	{
		return m_view.compare(pos1, n1, str, n2);
	}

	inline constexpr bool StringView::starts_with(const value_type ch) const
	{
		return (not empty()) && (front() == ch);
	}

	inline constexpr bool StringView::starts_with(const StringView text) const
	{
		return (m_view.size() >= text.size())
			&& (std::char_traits<value_type>::compare(m_view.data(), text.data(), text.size()) == 0);
	}

	inline bool StringView::ends_with(const value_type ch) const
	{
		return (not empty()) && (back() == ch);
	}

	inline constexpr bool StringView::ends_with(const StringView text) const
	{
		return (m_view.size() >= text.size())
			&& (std::char_traits<value_type>::compare(m_view.data() + m_view.size() - text.size(), text.data(), text.size()) == 0);
	}

	inline constexpr StringView::size_type StringView::indexOf(const StringView str, const size_type pos) const noexcept
	{
		return m_view.find(str.m_view, pos);
	}

	inline constexpr StringView::size_type StringView::indexOf(const value_type ch, const size_type pos) const noexcept
	{
		return m_view.find(ch, pos);
	}

	inline constexpr StringView::size_type StringView::indexOf(const value_type* str, const size_type pos, const size_type count) const noexcept
	{
		return m_view.find(str, pos, count);
	}

	inline constexpr StringView::size_type StringView::indexOf(const value_type* str, const size_type pos) const noexcept
	{
		return m_view.find(str, pos);
	}

	inline constexpr size_t StringView::indexOfNot(const value_type ch, const size_t pos) const noexcept
	{
		return m_view.find_first_not_of(ch, pos);
	}

	inline constexpr StringView::size_type StringView::lastIndexOf(const StringView str, const size_type pos) const noexcept
	{
		return m_view.rfind(str.m_view, pos);
	}

	inline constexpr StringView::size_type StringView::lastIndexOf(const value_type ch, const size_type pos) const noexcept
	{
		return m_view.rfind(ch, pos);
	}

	inline constexpr StringView::size_type StringView::lastIndexOf(const value_type* str, const size_type pos, const size_type count) const noexcept
	{
		return m_view.rfind(str, pos, count);
	}

	inline constexpr StringView::size_type StringView::lastIndexOf(const value_type* str, const size_type pos) const noexcept
	{
		return m_view.rfind(str, pos);
	}

	inline constexpr size_t StringView::lastIndexNotOf(const value_type ch, const size_t pos) const noexcept
	{
		return m_view.find_last_not_of(ch, pos);
	}

	inline constexpr size_t StringView::indexOfAny(const StringView anyof, const size_t pos) const noexcept
	{
		return m_view.find_first_of(anyof.m_view, pos);
	}

	inline constexpr size_t StringView::indexOfAny(const value_type* anyof, const size_t pos) const noexcept
	{
		return m_view.find_first_of(anyof, pos);
	}

	inline constexpr size_t StringView::lastIndexOfAny(const StringView anyof, const size_t pos) const noexcept
	{
		return m_view.find_last_of(anyof.m_view, pos);
	}

	inline constexpr size_t StringView::lastIndexOfAny(const value_type* anyof, const size_t pos) const noexcept
	{
		return m_view.find_last_of(anyof, pos);
	}

	inline constexpr size_t StringView::indexNotOfAny(const StringView anyof, const size_t pos) const noexcept
	{
		return m_view.find_first_not_of(anyof.m_view, pos);
	}

	inline constexpr size_t StringView::indexNotOfAny(const value_type* anyof, const size_t pos) const noexcept
	{
		return m_view.find_first_not_of(anyof, pos);
	}

	inline constexpr size_t StringView::lastIndexNotOfAny(const StringView anyof, const size_t pos) const noexcept
	{
		return m_view.find_last_not_of(anyof.m_view, pos);
	}

	inline constexpr size_t StringView::lastIndexNotOfAny(const value_type* anyof, const size_t pos) const noexcept
	{
		return m_view.find_last_not_of(anyof, pos);
	}
}
