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
	inline constexpr Vector4D<Type>::Vector4D(const value_type _x, const value_type _y, const value_type _z, const value_type _w) noexcept
		: x(_x)
		, y(_y) 
		, z(_z)
		, w(_w) {}

	template <class Type>
	template <class X, class Y, class Z, class W>
	inline constexpr Vector4D<Type>::Vector4D(const X _x, const Y _y, const Z _z, const W _w) noexcept
		: x(static_cast<value_type>(_x))
		, y(static_cast<value_type>(_y))
		, z(static_cast<value_type>(_z))
		, w(static_cast<value_type>(_w)) {}


	template <class Type>
	template <class U>
	inline constexpr Vector4D<Type>::Vector4D(const Vector4D<U>& v) noexcept
		: x(static_cast<value_type>(v.x))
		, y(static_cast<value_type>(v.y))
		, z(static_cast<value_type>(v.z))
		, w(static_cast<value_type>(v.w)) {}

	template <class Type>
	template <class X, class Y>
	inline constexpr Vector4D<Type>::Vector4D(const X _x, const Y _y, const Vector2D<value_type>& zw) noexcept
		: x(static_cast<value_type>(_x))
		, y(static_cast<value_type>(_y))
		, z(zw.x)
		, w(zw.y) {}

	template <class Type>
	template <class X, class W>
	inline constexpr Vector4D<Type>::Vector4D(const X _x, const Vector2D<value_type>& yz, const W _w) noexcept
		: x(static_cast<value_type>(_x))
		, y(yz.x)
		, z(yz.y)
		, w(static_cast<value_type>(_w)) {}

	template <class Type>
	template <class Z, class W>
	inline constexpr Vector4D<Type>::Vector4D(const Vector2D<value_type>& xy, const Z _z, const W _w) noexcept
		: x(xy.x)
		, y(xy.y)
		, z(static_cast<value_type>(_z))
		, w(static_cast<value_type>(_w)) {}

	template <class Type>
	inline constexpr Vector4D<Type>::Vector4D(const Vector2D<value_type>& xy, const Vector2D<value_type>& zw) noexcept
		: x(xy.x)
		, y(xy.y)
		, z(zw.x)
		, w(zw.y) {}

	template <class Type>
	template <class X>
	inline constexpr Vector4D<Type>::Vector4D(const X _x, const Vector3D<value_type>& yzw) noexcept
		: x(static_cast<value_type>(_x))
		, y(yzw.x)
		, z(yzw.y)
		, w(yzw.z) {}

	template <class Type>
	template <class Z>
	inline constexpr Vector4D<Type>::Vector4D(const Vector3D<value_type>& xyz, const Z _z) noexcept
		: x(xyz.x)
		, y(xyz.y)
		, z(xyz.z)
		, w(static_cast<value_type>(_z)) {}

	template <class Type>
	inline constexpr typename Vector4D<Type>::value_type Vector4D<Type>::elem(const size_t index) const noexcept
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
		else if (index == 3)
		{
			return w;
		}
		else
		{
			return 0;
		}
	}

	template <class Type>
	inline typename Vector4D<Type>::value_type* Vector4D<Type>::getPointer() noexcept
	{
		return &x;
	}

	template <class Type>
	inline const typename Vector4D<Type>::value_type* Vector4D<Type>::getPointer() const noexcept
	{
		return &x;
	}
}
