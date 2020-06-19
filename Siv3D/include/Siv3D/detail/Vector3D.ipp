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
	template <class Type>
	inline constexpr Vector3D<Type>::Vector3D(const value_type _x, const value_type _y, const value_type _z) noexcept
		: x(_x)
		, y(_y)
		, z(_z) {}

	template <class Type>
	template <class X, class Y, class Z>
	inline constexpr Vector3D<Type>::Vector3D(const X _x, const Y _y, const Z _z) noexcept
		: x(static_cast<value_type>(_x))
		, y(static_cast<value_type>(_y))
		, z(static_cast<value_type>(_z)) {}

	template <class Type>
	template <class U>
	inline constexpr Vector3D<Type>::Vector3D(const Vector3D<U>& v) noexcept
		: x(static_cast<value_type>(v.x))
		, y(static_cast<value_type>(v.y))
		, z(static_cast<value_type>(v.z)) {}

	template <class Type>
	template <class Z>
	inline constexpr Vector3D<Type>::Vector3D(const Vector2D<value_type>& xy, const Z _z) noexcept
		: x(xy.x)
		, y(xy.y)
		, z(static_cast<value_type>(_z)) {}

	template <class Type>
	template <class X>
	inline constexpr Vector3D<Type>::Vector3D(const X _x, const Vector2D<value_type>& yz) noexcept
		: x(static_cast<value_type>(_x))
		, y(yz.x)
		, z(yz.y) {}

	template <class Type>
	inline constexpr typename Vector3D<Type>::value_type Vector3D<Type>::elem(const size_t index) const noexcept
	{
		if (index == 0)
		{
			return x;
		}
		else if (index == 1)
		{
			return y;
		}
		else if (index == 2)
		{
			return z;
		}
		else
		{
			return 0;
		}
	}

	template <class Type>
	inline typename Vector3D<Type>::value_type* Vector3D<Type>::getPointer() noexcept
	{
		return &x;
	}

	template <class Type>
	inline const typename Vector3D<Type>::value_type* Vector3D<Type>::getPointer() const noexcept
	{
		return &x;
	}
}
