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
# include <vector>
# include "Common.hpp"
# include "PredefinedNamedParameter.hpp"

namespace s3d
{
	/// @brief 動的配列
	/// @tparam Type 要素の型
	/// @tparam Allocator アロケータ
	template <class Type, class Allocator = std::allocator<Type>>
	class Array : protected std::vector<Type, Allocator>
	{
	private:

		using base_type = std::vector<Type, Allocator>;

	public:

		using typename base_type::value_type;
		using typename base_type::pointer;
		using typename base_type::const_pointer;
		using typename base_type::reference;
		using typename base_type::const_reference;
		using typename base_type::iterator;
		using typename base_type::const_iterator;
		using typename base_type::reverse_iterator;
		using typename base_type::const_reverse_iterator;
		using typename base_type::size_type;
		using typename base_type::difference_type;
		using typename base_type::allocator_type;

		using base_type::vector;
		using base_type::operator=;
		using base_type::assign;
		using base_type::get_allocator;
		using base_type::front;
		using base_type::back;
		using base_type::data;
		using base_type::begin;
		using base_type::cbegin;
		using base_type::end;
		using base_type::cend;
		using base_type::rbegin;
		using base_type::crbegin;
		using base_type::rend;
		using base_type::crend;
		using base_type::empty;
		using base_type::size;
		using base_type::max_size;
		using base_type::reserve;
		using base_type::capacity;
		using base_type::shrink_to_fit;
		using base_type::clear;
		using base_type::insert;
		using base_type::emplace;
		using base_type::erase;
		using base_type::push_back;
		using base_type::emplace_back;
		using base_type::pop_back;
		using base_type::resize;

		Array() = default;

		Array(const Array& other) = default;

		Array(Array&& other) = default;

		Array& operator =(const Array& other) = default;

		Array& operator =(Array&& other) = default;

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		Array(size_type size, Arg::generator_<Fty> generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>* = nullptr>
		Array(size_type size, Arg::indexedGenerator_<Fty> indexedGenerator);

		void swap(Array& other) noexcept;

		[[nodiscard]]
		bool isEmpty() const noexcept;

		[[nodiscard]]
		explicit operator bool() const noexcept;

		void release();

		[[nodiscard]]
		size_t size_bytes() const noexcept;

		void push_front(const value_type& value);

		void push_front(value_type&& value);

		void pop_front();

		[[nodiscard]]
		const value_type& operator[](size_t index) const&;

		[[nodiscard]]
		value_type& operator[](size_t index) &;

		[[nodiscard]]
		value_type operator[](size_t index) &&;

		const value_type& at(size_t index) const&;

		value_type& at(size_t index) &;

		value_type at(size_t index) &&;

		Array& operator <<(const value_type& value);

		Array& operator <<(value_type&& value);








		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>* = nullptr>
		static Array Generate(size_type size, Fty generator);

		template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>* = nullptr>
		static Array IndexedGenerate(size_type size, Fty indexedGenerator);
	};
}

# include "detail/Array.ipp"
