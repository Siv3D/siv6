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
# include <string_view>
# include <string>
# include "Fwd.hpp"

namespace s3d
{
	class StringView
	{
	public:

		using string_view_type			= std::u32string_view;
		using traits_type				= typename string_view_type::traits_type;
		using value_type				= typename string_view_type::value_type;
		using pointer					= typename string_view_type::pointer;
		using const_pointer				= typename string_view_type::const_pointer;
		using reference					= typename string_view_type::reference;
		using const_reference			= typename string_view_type::const_reference;
		using const_iterator			= typename string_view_type::const_iterator;
		using iterator					= typename string_view_type::iterator;
		using const_reverse_iterator	= typename string_view_type::const_reverse_iterator;
		using reverse_iterator			= typename string_view_type::reverse_iterator;
		using size_type					= typename string_view_type::size_type;
		using difference_type			= typename string_view_type::difference_type;

	private:

		string_view_type m_view;

	public:

		static constexpr size_type npos{ static_cast<size_type>(-1) };

		SIV3D_NODISCARD_CXX20
		constexpr StringView() = default;

		SIV3D_NODISCARD_CXX20
		constexpr StringView(const StringView&) = default;

		SIV3D_NODISCARD_CXX20
		StringView(const std::u32string& s) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr StringView(std::u32string_view s) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr StringView(const value_type* s, size_type length) noexcept;

		SIV3D_NODISCARD_CXX20
		constexpr StringView(const value_type* s) noexcept;

		constexpr StringView& operator =(const StringView&) = default;

		[[nodiscard]]
		constexpr const_iterator begin() const noexcept;

		[[nodiscard]]
		constexpr const_iterator end() const noexcept;

		[[nodiscard]]
		constexpr const_iterator cbegin() const noexcept;

		[[nodiscard]]
		constexpr const_iterator cend() const noexcept;

		[[nodiscard]]
		constexpr const_reverse_iterator rbegin() const noexcept;

		[[nodiscard]]
		constexpr const_reverse_iterator rend() const noexcept;

		[[nodiscard]]
		constexpr const_reverse_iterator crbegin() const noexcept;

		[[nodiscard]]
		constexpr const_reverse_iterator crend() const noexcept;

		[[nodiscard]]
		constexpr const_reference operator[](size_type index) const;

		[[nodiscard]]
		constexpr const_reference at(size_type index) const;

		[[nodiscard]]
		constexpr const_reference front() const;

		[[nodiscard]]
		constexpr const_reference back() const;

		[[nodiscard]]
		constexpr const_pointer data() const noexcept;

		[[nodiscard]]
		constexpr size_type size() const noexcept;

		[[nodiscard]]
		constexpr size_type size_bytes() const noexcept;

		[[nodiscard]]
		constexpr size_type length() const noexcept;

		[[nodiscard]]
		constexpr size_type max_size() const noexcept;

		[[nodiscard]]
		constexpr bool empty() const noexcept;

		[[nodiscard]]
		constexpr bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit constexpr operator bool() const noexcept;

		constexpr void remove_prefix(size_type n) noexcept;

		constexpr void remove_suffix(size_type n) noexcept;

		constexpr void swap(StringView& other) noexcept;

		constexpr void clear() noexcept;

		constexpr size_type copy(value_type* dst, size_type n, size_type pos = 0) const;

		[[nodiscard]]
		constexpr StringView substr(size_type pos = 0, size_type n = npos) const;

		[[nodiscard]]
		constexpr int32 compare(StringView sv) const noexcept;

		[[nodiscard]]
		constexpr int32 compare(size_type pos1, size_type n1, StringView sv) const noexcept;

		[[nodiscard]]
		constexpr int32 compare(size_type pos1, size_type n1, StringView sv, size_type pos2, size_type n2) const noexcept;

		[[nodiscard]]
		constexpr int32 compare(const value_type* str) const noexcept;

		[[nodiscard]]
		constexpr int32 compare(size_type pos1, size_type n1, const value_type* str) const noexcept;

		[[nodiscard]]
		constexpr int32 compare(size_type pos1, size_type n1, const value_type* str, size_type n2) const noexcept;

		[[nodiscard]]
		constexpr bool starts_with(value_type ch) const;

		[[nodiscard]]
		constexpr bool starts_with(StringView text) const;

		[[nodiscard]]
		bool ends_with(value_type ch) const;

		[[nodiscard]]
		constexpr bool ends_with(StringView text) const;

		[[nodiscard]]
		constexpr size_type indexOf(StringView str, size_type pos = 0) const noexcept;

		[[nodiscard]]
		constexpr size_type indexOf(value_type ch, size_type pos = 0) const noexcept;

		[[nodiscard]]
		constexpr size_type indexOf(const value_type* str, size_type pos, size_type count) const noexcept;

		[[nodiscard]]
		constexpr size_type indexOf(const value_type* str, size_type pos = 0) const noexcept;

		[[nodiscard]]
		constexpr size_t indexOfNot(value_type ch, size_t pos = 0) const noexcept;

		[[nodiscard]]
		constexpr size_type lastIndexOf(StringView str, size_type pos = npos) const noexcept;

		[[nodiscard]]
		constexpr size_type lastIndexOf(value_type ch, size_type pos = npos) const noexcept;

		[[nodiscard]]
		constexpr size_type lastIndexOf(const value_type* str, size_type pos, size_type count) const noexcept;

		[[nodiscard]]
		constexpr size_type lastIndexOf(const value_type* str, size_type pos = npos) const noexcept;

		[[nodiscard]]
		constexpr size_t lastIndexNotOf(value_type ch, size_t pos = npos) const noexcept;

		[[nodiscard]]
		constexpr size_t indexOfAny(StringView anyof, size_t pos = 0) const noexcept;

		[[nodiscard]]
		constexpr size_t indexOfAny(const value_type* anyof, size_t pos = 0) const noexcept;

		[[nodiscard]]
		constexpr size_t lastIndexOfAny(StringView anyof, size_t pos = 0) const noexcept;

		[[nodiscard]]
		constexpr size_t lastIndexOfAny(const value_type* anyof, size_t pos = 0) const noexcept;

		[[nodiscard]]
		constexpr size_t indexNotOfAny(StringView anyof, size_t pos = 0) const noexcept;

		[[nodiscard]]
		constexpr size_t indexNotOfAny(const value_type* anyof, size_t pos = 0) const noexcept;

		[[nodiscard]]
		constexpr size_t lastIndexNotOfAny(StringView anyof, size_t pos = 0) const noexcept;

		[[nodiscard]]
		constexpr size_t lastIndexNotOfAny(const value_type* anyof, size_t pos = 0) const noexcept;

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

		[[nodiscard]]
		friend constexpr bool operator ==(StringView x, StringView y) noexcept
		{
			return (x.compare(y) == 0);
		}

		[[nodiscard]]
		friend constexpr bool operator !=(StringView x, StringView y) noexcept
		{
			return (x.compare(y) != 0);
		}

		[[nodiscard]]
		friend constexpr bool operator <(StringView x, StringView y) noexcept
		{
			return (x.compare(y) < 0);
		}

		[[nodiscard]]
		friend constexpr bool operator <=(StringView x, StringView y) noexcept
		{
			return (x.compare(y) <= 0);
		}

		[[nodiscard]]
		friend constexpr bool operator >(StringView x, StringView y) noexcept
		{
			return (x.compare(y) > 0);
		}

		[[nodiscard]]
		friend constexpr bool operator >=(StringView x, StringView y) noexcept
		{
			return (x.compare(y) >= 0);
		}

		friend std::ostream& operator <<(std::ostream& output, const StringView& value)
		{
			return (output << value.narrow());
		}

		friend std::wostream& operator <<(std::wostream& output, const StringView& value)
		{
			return (output << value.toWstr());
		}
	};

	inline namespace Literals
	{
		inline namespace StringViewLiterals
		{
			[[nodiscard]]
			constexpr StringView operator ""_sv(const char32_t* s, const size_t length) noexcept
			{
				return StringView(s, length);
			}
		}
	}

	using FilePathView = StringView;
}

# include "StringView.ipp"
