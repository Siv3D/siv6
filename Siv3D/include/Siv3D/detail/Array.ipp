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
	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>*>
	inline Array<Type, Allocator>::Array(const size_type size, Arg::generator_<Fty> generator)
		: Array(Generate<Fty>(size, *generator)) {}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>*>
	inline Array<Type, Allocator>::Array(const size_type size, Arg::indexedGenerator_<Fty> indexedGenerator)
		: Array(IndexedGenerate<Fty>(size, *indexedGenerator)) {}

	template <class Type, class Allocator>
	inline void Array<Type, Allocator>::swap(Array& other) noexcept
	{
		base_type::swap(other);
	}

	template <class Type, class Allocator>
	inline bool Array<Type, Allocator>::isEmpty() const noexcept
	{
		return empty();
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>::operator bool() const noexcept
	{
		return !empty();
	}

	template <class Type, class Allocator>
	inline void Array<Type, Allocator>::release()
	{
		clear();

		shrink_to_fit();
	}

	template <class Type, class Allocator>
	inline size_t Array<Type, Allocator>::size_bytes() const noexcept
	{
		static_assert(std::is_trivially_copyable_v<value_type>, "Array::size_bytes() value_type must be trivially copyable.");

		return size() * sizeof(value_type);
	}

	template <class Type, class Allocator>
	inline void Array<Type, Allocator>::push_front(const value_type& value)
	{
		insert(begin(), value);
	}

	template <class Type, class Allocator>
	inline void Array<Type, Allocator>::push_front(value_type&& value)
	{
		insert(begin(), std::move(value));
	}

	template <class Type, class Allocator>
	inline void Array<Type, Allocator>::pop_front()
	{
		erase(begin());
	}

	template <class Type, class Allocator>
	inline const typename Array<Type, Allocator>::value_type& Array<Type, Allocator>::operator[](const size_t index) const&
	{
		return base_type::operator[](index);
	}

	template <class Type, class Allocator>
	inline typename Array<Type, Allocator>::value_type& Array<Type, Allocator>::operator[](const size_t index) &
	{
		return base_type::operator[](index);
	}

	template <class Type, class Allocator>
	inline typename Array<Type, Allocator>::value_type Array<Type, Allocator>::operator[](const size_t index) &&
	{
		return std::move(base_type::operator[](index));
	}

	template <class Type, class Allocator>
	inline const typename Array<Type, Allocator>::value_type& Array<Type, Allocator>::at(const size_t index) const&
	{
		return base_type::at(index);
	}

	template <class Type, class Allocator>
	inline typename Array<Type, Allocator>::value_type& Array<Type, Allocator>::at(const size_t index) &
	{
		return base_type::at(index);
	}

	template <class Type, class Allocator>
	inline typename Array<Type, Allocator>::value_type Array<Type, Allocator>::at(const size_t index) &&
	{
		return std::move(base_type::at(index));
	}

	template <class Type, class Allocator>
	inline typename Array<Type, Allocator>& Array<Type, Allocator>::operator <<(const value_type& value)
	{
		push_back(value);

		return *this;
	}

	template <class Type, class Allocator>
	inline Array<Type, Allocator>& Array<Type, Allocator>::operator <<(value_type&& value)
	{
		push_back(std::forward<value_type>(value));

		return *this;
	}






	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::Generate(const size_type size, Fty generator)
	{
		Array new_array;
		new_array.reserve(size);

		for (size_type i = 0; i < size; ++i)
		{
			new_array.push_back(generator());
		}

		return new_array;
	}

	template <class Type, class Allocator>
	template <class Fty, std::enable_if_t<std::is_invocable_r_v<Type, Fty, size_t>>*>
	inline Array<Type, Allocator> Array<Type, Allocator>::IndexedGenerate(const size_type size, Fty indexedGenerator)
	{
		Array new_array;
		new_array.reserve(size);

		for (size_type i = 0; i < size; ++i)
		{
			new_array.push_back(indexedGenerator(i));
		}

		return new_array;
	}
}
