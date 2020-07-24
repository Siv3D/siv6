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
	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt::BigInt(const Integer i)
		: BigInt(static_cast<int64>(i)) {}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt::BigInt(const Integer i)
		: BigInt(static_cast<uint64>(i)) {}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::assign(const Integer i)
	{
		return assign(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::assign(const Integer i)
	{
		return assign(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator =(const Integer i)
	{
		return assign(i);
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator =(const Integer i)
	{
		return assign(i);
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator +(Integer i) const
	{
		return operator +(static_cast<int64>(i));
	}
		
	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator +(Integer i) const
	{
		return operator +(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator +=(Integer i)
	{
		return operator +=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator +=(Integer i)
	{
		return operator +=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator -(Integer i) const
	{
		return operator -(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator -(Integer i) const
	{
		return operator -(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator -=(Integer i)
	{ 
		return operator -=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator -=(Integer i)
	{
		return operator -=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator *(Integer i) const
	{
		return operator *(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator *(Integer i) const
	{
		return operator *(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator *=(Integer i)
	{
		return operator *=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator *=(Integer i)
	{
		return operator *=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator /(Integer i) const
	{
		return operator /(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator /(Integer i) const
	{
		return operator /(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator /=(Integer i)
	{
		return operator /=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator /=(Integer i)
	{
		return operator /=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator %(Integer i) const
	{
		return operator %(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator %(Integer i) const
	{
		return operator %(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator %=(Integer i)
	{
		return operator %=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator %=(Integer i)
	{
		return operator %=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator &(Integer i) const
	{
		return operator &(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator &(Integer i) const
	{
		return operator &(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator &=(Integer i)
	{
		return operator &=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator &=(Integer i)
	{
		return operator &=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator |(Integer i) const
	{
		return operator |(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator |(Integer i) const
	{
		return operator |(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator |=(Integer i)
	{
		return operator |=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator |=(Integer i)
	{
		return operator |=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator ^(Integer i) const
	{
		return operator ^(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator ^(Integer i) const
	{
		return operator ^(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator ^=(Integer i)
	{
		return operator ^=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator ^=(Integer i)
	{
		return operator ^=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator <<(Integer i) const
	{
		return operator <<(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator <<(Integer i) const
	{
		return operator <<(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator <<=(Integer i)
	{
		return operator <<=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator <<=(Integer i)
	{
		return operator <<=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt BigInt::operator >>(Integer i) const
	{
		return operator >> (static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt BigInt::operator >>(Integer i) const
	{
		return operator >> (static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline BigInt& BigInt::operator >>=(Integer i)
	{
		return operator >>=(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline BigInt& BigInt::operator >>=(Integer i)
	{
		return operator >>=(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_SIGNED_INTEGRAL_
	inline int32 BigInt::compare(Integer i) const
	{
		return compare(static_cast<int64>(i));
	}

	SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
	inline int32 BigInt::compare(Integer i) const
	{
		return compare(static_cast<uint64>(i));
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline int32 BigInt::compare(Float f) const
	{
		return compare(static_cast<long double>(f));
	}

	inline BigInt::operator size_t() const
	{
		return asSize_t();
	}

	inline BigInt::operator float() const
	{
		return asFloat();
	}

	inline BigInt::operator double() const
	{
		return asDouble();
	}
}

template <>
inline void std::swap(s3d::BigInt& a, s3d::BigInt& b) noexcept
{
	a.swap(b);
}
