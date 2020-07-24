﻿//-----------------------------------------------
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
# include <memory>
# include "Fwd.hpp"
# include "Concepts.hpp"
# include "String.hpp"

# if __cpp_lib_concepts
	# define SIV3D_CONCEPT_SIGNED_INTEGRAL template <Concept::SignedIntegral Integer>
	# define SIV3D_CONCEPT_SIGNED_INTEGRAL_ template <Concept::SignedIntegral Integer>
	# define SIV3D_CONCEPT_UNSIGNED_INTEGRAL template <Concept::UnsignedIntegral Integer>
	# define SIV3D_CONCEPT_UNSIGNED_INTEGRAL_ template <Concept::UnsignedIntegral Integer>
	# define SIV3D_CONCEPT_FLOATING_POINT template <Concept::FloatingPoint Float>
	# define SIV3D_CONCEPT_FLOATING_POINT_ template <Concept::FloatingPoint Float>
# else
	# define SIV3D_CONCEPT_SIGNED_INTEGRAL template <class Integer, std::enable_if_t<(std::is_integral_v<Integer>&& std::is_signed_v<Integer>)>* = nullptr>
	# define SIV3D_CONCEPT_SIGNED_INTEGRAL_ template <class Integer, std::enable_if_t<(std::is_integral_v<Integer>&& std::is_signed_v<Integer>)>*>
	# define SIV3D_CONCEPT_UNSIGNED_INTEGRAL template <class Integer, std::enable_if_t<(std::is_integral_v<Integer>&& !std::is_signed_v<Integer>)>* = nullptr>
	# define SIV3D_CONCEPT_UNSIGNED_INTEGRAL_ template <class Integer, std::enable_if_t<(std::is_integral_v<Integer>&& !std::is_signed_v<Integer>)>*>
	# define SIV3D_CONCEPT_FLOATING_POINT template <class Float, std::enable_if_t<std::is_floating_point_v<Float>>* = nullptr>
	# define SIV3D_CONCEPT_FLOATING_POINT_ template <class Float, std::enable_if_t<std::is_floating_point_v<Float>>*>
# endif

namespace s3d
{
	class BigInt
	{
	private:

		struct BigIntDetail;
		
		std::unique_ptr<BigIntDetail> pImpl;
		
		friend class BigFloat;
		friend BigInt operator /(int64 a, const BigInt& b);
		friend BigInt operator /(uint64 a, const BigInt& b);
		friend BigInt operator %(int64 a, const BigInt& b);
		friend BigInt operator %(uint64 a, const BigInt& b);

	public:

		BigInt();
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt(Integer i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt(Integer i);
		
		BigInt(int64 i);
		
		BigInt(uint64 i);
		
		explicit BigInt(std::string_view number);
		
		explicit BigInt(StringView number);
		
		BigInt(const BigInt& other);
		
		BigInt(BigInt&& other) noexcept;

		//////////////////////////////////////////////////
		//
		//	assign
		//
		//////////////////////////////////////////////////

		BigInt& assign(int64 i);
		
		BigInt& assign(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& assign(Integer i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& assign(Integer i);
		
		BigInt& assign(std::string_view number);
		
		BigInt& assign(StringView number);
		
		BigInt& assign(const BigInt& other);
		
		BigInt& assign(BigInt&& other) noexcept;

		//////////////////////////////////////////////////
		//
		//	=
		//
		//////////////////////////////////////////////////

		BigInt& operator =(int64 i);
		
		BigInt& operator =(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator =(Integer i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator =(Integer i);
		
		BigInt& operator =(const std::string_view number);
		
		BigInt& operator =(const StringView number);
		
		BigInt& operator =(const BigInt& other);
		
		BigInt& operator =(BigInt&& other) noexcept;

		//////////////////////////////////////////////////
		//
		//	+
		//
		//////////////////////////////////////////////////
		
		[[nodiscard]]
		const BigInt& operator +() const;
		
		BigInt& operator ++();
		
		BigInt operator ++(int);
		
		[[nodiscard]]
		BigInt operator +(int64 i) const;
		
		[[nodiscard]]
		BigInt operator +(uint64 i) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL	
		[[nodiscard]]
		BigInt operator +(Integer i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator +(Integer i) const;
		
		[[nodiscard]]
		BigInt operator +(const BigInt& i) const;
		
		BigInt& operator +=(int64 i);
		
		BigInt& operator +=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL	
		BigInt& operator +=(Integer i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator +=(Integer i);
		
		BigInt& operator +=(const BigInt& i);

		//////////////////////////////////////////////////
		//
		//	-
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator -() const&;
		
		[[nodiscard]]
		BigInt operator -()&&;
		
		BigInt& operator --();
		
		BigInt operator --(int);
		
		[[nodiscard]]
		BigInt operator -(int64 i) const;
		
		[[nodiscard]]
		BigInt operator -(uint64 i) const;

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator -(Integer i) const;

		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator -(Integer i) const;

		[[nodiscard]]
		BigInt operator -(const BigInt& i) const;
		
		BigInt& operator -=(int64 i);
		
		BigInt& operator -=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator -=(Integer i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator -=(Integer i);
		
		BigInt& operator -=(const BigInt& i);

		//////////////////////////////////////////////////
		//
		//	*
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator *(int64 i) const;

		[[nodiscard]]
		BigInt operator *(uint64 i) const;

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator *(Integer i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator *(Integer i) const;
		
		[[nodiscard]]
		BigInt operator *(const BigInt& i) const;
		
		BigInt& operator *=(int64 i);
		
		BigInt& operator *=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator *=(Integer i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator *=(Integer i);
		
		BigInt& operator *=(const BigInt& i);

		//////////////////////////////////////////////////
		//
		//	/
		//
		//////////////////////////////////////////////////

		[[nodiscard]]		
		BigInt operator /(int64 i) const;

		[[nodiscard]]
		BigInt operator /(uint64 i) const;

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator /(Integer i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator /(Integer i) const;

		[[nodiscard]]
		BigInt operator /(const BigInt& i) const;

		BigInt& operator /=(int64 i);
		
		BigInt& operator /=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator /=(Integer i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator /=(Integer i);
		
		BigInt& operator /=(const BigInt& i);

		//////////////////////////////////////////////////
		//
		//	%
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator %(int64 i) const;
		
		[[nodiscard]]
		BigInt operator %(uint64 i) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator %(Integer i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator %(Integer i) const;
		
		[[nodiscard]]
		BigInt operator %(const BigInt& i) const;
		
		BigInt& operator %=(int64 i);
		
		BigInt& operator %=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator %=(Integer i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL	
		BigInt& operator %=(Integer i);
		
		BigInt& operator %=(const BigInt& i);

		//////////////////////////////////////////////////
		//
		//	&
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator &(int64 i) const;
		
		[[nodiscard]]
		BigInt operator &(uint64 i) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator &(Integer i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator &(Integer i) const;
		
		[[nodiscard]]
		BigInt operator &(const BigInt& i) const;
		
		BigInt& operator &=(int64 i);
		
		BigInt& operator &=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator &=(Integer i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator &=(Integer i);
		
		BigInt& operator &=(const BigInt& i);

		//////////////////////////////////////////////////
		//
		//	|
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator |(int64 i) const;
		
		[[nodiscard]]
		BigInt operator |(uint64 i) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator |(Integer i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator |(Integer i) const;
		
		[[nodiscard]]
		BigInt operator |(const BigInt& i) const;
		
		BigInt& operator |=(int64 i);
		
		BigInt& operator |=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator |=(Integer i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator |=(Integer i);
		
		BigInt& operator |=(const BigInt& i);

		//////////////////////////////////////////////////
		//
		//	^
		//
		//////////////////////////////////////////////////

		[[nodiscard]]	
		BigInt operator ^(int64 i) const;
		
		[[nodiscard]]
		BigInt operator ^(uint64 i) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator ^(Integer i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator ^(Integer i) const;
		
		[[nodiscard]]
		BigInt operator ^(const BigInt& i) const;
		
		BigInt& operator ^=(int64 i);
		
		BigInt& operator ^=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator ^=(Integer i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator ^=(Integer i);
		
		BigInt& operator ^=(const BigInt& i);

		//////////////////////////////////////////////////
		//
		//	<<
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator <<(int64 i) const;
		
		[[nodiscard]]
		BigInt operator <<(uint64 i) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator <<(Integer i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator <<(Integer i) const;
		
		BigInt& operator <<=(int64 i);
		
		BigInt& operator <<=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator <<=(Integer i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator <<=(Integer i);

		//////////////////////////////////////////////////
		//
		//	>>
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		BigInt operator >>(int64 i) const;
		
		[[nodiscard]]
		BigInt operator >>(uint64 i) const;

		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator >>(Integer i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		BigInt operator >>(Integer i) const;
		
		BigInt& operator >>=(int64 i);
		
		BigInt& operator >>=(uint64 i);
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		BigInt& operator >>=(Integer i);
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		BigInt& operator >>=(Integer i);

		//////////////////////////////////////////////////
		//
		//	compare
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		int32 compare(int64 i) const;
		
		[[nodiscard]]
		int32 compare(uint64 i) const;
		
		[[nodiscard]]
		int32 compare(long double f) const;
		
		SIV3D_CONCEPT_SIGNED_INTEGRAL
		[[nodiscard]]
		int32 compare(Integer i) const;
		
		SIV3D_CONCEPT_UNSIGNED_INTEGRAL
		[[nodiscard]]
		int32 compare(Integer i) const;
		
		SIV3D_CONCEPT_FLOATING_POINT
		[[nodiscard]]
		int32 compare(Float f) const;
		
		[[nodiscard]]
		int32 compare(const BigInt& i) const;

		//////////////////////////////////////////////////
		//
		//	utilities
		//
		//////////////////////////////////////////////////

		[[nodiscard]]
		explicit operator bool() const;
		
		[[nodiscard]]
		bool isZero() const;
		
		[[nodiscard]]
		int32 sign() const;
		
		[[nodiscard]]
		BigInt abs() const;
		
		[[nodiscard]]
		BigInt pow(uint32 x) const;
		
		void divmod(const BigInt& x, BigInt& q, BigInt& r) const;
		
		[[nodiscard]]
		uint32 lsb() const;

		[[nodiscard]]
		bool bitTest(uint32 index) const;
		
		BigInt& bitSet(uint32 index, bool value);
		
		BigInt& bitFlip(uint32 index);

		[[nodiscard]]
		int32 asInt32() const;
		
		[[nodiscard]]
		int64 asInt64() const;
		
		[[nodiscard]]
		uint32 asUint32() const;
		
		[[nodiscard]]
		uint64 asUint64() const;
		
		[[nodiscard]]
		size_t asSize_t() const;
		
		[[nodiscard]]
		float asFloat() const;
		
		[[nodiscard]]
		double asDouble() const;
		
		[[nodiscard]]
		BigFloat asBigFloat() const;

		[[nodiscard]]
		explicit operator size_t() const;

		[[nodiscard]]
		explicit operator float() const;

		[[nodiscard]]
		explicit operator double() const;

		[[nodiscard]]
		explicit operator BigFloat() const;

		[[nodiscard]]
		std::string stdStr() const;

		[[nodiscard]]
		std::wstring stdWstr() const;

		[[nodiscard]]
		String str() const;

		void swap(BigInt& other) noexcept;

		//size_t hash() const;

		friend BigInt GCD(const BigInt&, const BigInt&);
		friend BigInt LCM(const BigInt&, const BigInt&);
	};

	/*
	template <class Type, std::enable_if_t<std::is_integral_v<Type>>* = nullptr>
	[[nodiscard]] inline BigInt operator +(const Type& a, const BigInt& b)
	{
		return b + a;
	}

	template <class Type, std::enable_if_t<std::is_integral_v<Type>>* = nullptr>
	[[nodiscard]] inline BigInt operator -(const Type& a, const BigInt& b)
	{
		return -b + a;
	}

	template <class Type, std::enable_if_t<std::is_integral_v<Type>>* = nullptr>
	[[nodiscard]] inline BigInt operator *(const Type& a, const BigInt& b)
	{
		return b * a;
	}

	template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
	[[nodiscard]] inline BigInt operator /(Integer a, const BigInt& b)
	{
		return static_cast<int64>(a) / b;
	}

	template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
	[[nodiscard]] inline BigInt operator /(Integer a, const BigInt& b)
	{
		return static_cast<uint64>(a) / b;
	}

	[[nodiscard]] BigInt operator /(int64 a, const BigInt& b);
	[[nodiscard]] BigInt operator /(uint64 a, const BigInt& b);

	template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && std::is_signed_v<Integer>)>* = nullptr>
	[[nodiscard]] inline BigInt operator %(Integer a, const BigInt& b)
	{
		return static_cast<int64>(a) / b;
	}

	template <class Integer, std::enable_if_t<(std::is_integral_v<Integer> && !std::is_signed_v<Integer>)>* = nullptr>
	[[nodiscard]] inline BigInt operator %(Integer a, const BigInt& b)
	{
		return static_cast<uint64>(a) / b;
	}

	[[nodiscard]] BigInt operator %(int64 a, const BigInt& b);
	[[nodiscard]] BigInt operator %(uint64 a, const BigInt& b);

	template <class Type, std::enable_if_t<std::is_integral_v<Type>>* = nullptr>
	[[nodiscard]] inline BigInt operator &(const Type& a, const BigInt& b)
	{
		return b & a;
	}

	template <class Type, std::enable_if_t<std::is_integral_v<Type>>* = nullptr>
	[[nodiscard]] inline BigInt operator |(const Type& a, const BigInt& b)
	{
		return b | a;
	}

	template <class Type, std::enable_if_t<std::is_integral_v<Type>>* = nullptr>
	[[nodiscard]] inline BigInt operator ^(const Type& a, const BigInt& b)
	{
		return b ^ a;
	}

	[[nodiscard]] BigInt GCD(const BigInt& a, const BigInt& b);

	[[nodiscard]] BigInt LCM(const BigInt& a, const BigInt& b);

	[[nodiscard]] bool IsPrime(uint64 n);

	inline namespace Literals
	{
		inline namespace BigNumLiterals
		{
			[[nodiscard]] BigInt operator ""_big(unsigned long long int i);

			[[nodiscard]] BigInt operator ""_big(const char* number, size_t);

			[[nodiscard]] BigInt operator ""_big(const char32* number, size_t);
		}
	}

	[[nodiscard]] inline bool operator ==(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) == 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator ==(const BigInt& a, Number b)
	{
		return a.compare(b) == 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator ==(Number a, const BigInt& b)
	{
		return b.compare(a) == 0;
	}

	[[nodiscard]] inline bool operator !=(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) != 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator !=(const BigInt& a, Number b)
	{
		return a.compare(b) != 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator !=(Number a, const BigInt& b)
	{
		return b.compare(a) != 0;
	}

	[[nodiscard]] inline bool operator <(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) < 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator <(const BigInt& a, Number b)
	{
		return a.compare(b) < 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator <(Number a, const BigInt& b)
	{
		return b.compare(a) < 0;
	}

	[[nodiscard]] inline bool operator <=(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) <= 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator <=(const BigInt& a, Number b)
	{
		return a.compare(b) <= 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator <=(Number a, const BigInt& b)
	{
		return b.compare(a) <= 0;
	}

	[[nodiscard]] inline bool operator >(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) > 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator >(const BigInt& a, Number b)
	{
		return a.compare(b) > 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator >(Number a, const BigInt& b)
	{
		return b.compare(a) > 0;
	}

	[[nodiscard]] inline bool operator >=(const BigInt& a, const BigInt& b)
	{
		return a.compare(b) >= 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator >=(const BigInt& a, Number b)
	{
		return a.compare(b) >= 0;
	}

	template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>>* = nullptr>
	[[nodiscard]] inline bool operator >=(Number a, const BigInt& b)
	{
		return b.compare(a) >= 0;
	}
	*/
}

template <>
inline void std::swap(s3d::BigInt& a, s3d::BigInt& b) noexcept;

# include "detail/BigInt.ipp"

# undef SIV3D_CONCEPT_SIGNED_INTEGRAL
# undef SIV3D_CONCEPT_SIGNED_INTEGRAL_
# undef SIV3D_CONCEPT_UNSIGNED_INTEGRAL
# undef SIV3D_CONCEPT_UNSIGNED_INTEGRAL_
# undef SIV3D_CONCEPT_FLOATING_POINT
# undef SIV3D_CONCEPT_FLOATING_POINT_
