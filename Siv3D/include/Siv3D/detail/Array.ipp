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
}
