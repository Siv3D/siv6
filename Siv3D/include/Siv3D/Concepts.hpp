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
# include <type_traits>
# if  __has_include(<concepts>)
#	include <concepts>
# endif

# if __cpp_lib_concepts

namespace s3d
{
	namespace Concept
	{
		/// @brief 整数型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept Integral = std::is_integral_v<Type>;
		
		/// @brief 符号付整数型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept SignedIntegral = std::integral<Type> && (Type(-1) < Type(0));

		/// @brief 符号なし整数型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept UnsignedIntegral = std::integral<Type> && !SignedIntegral<Type>;

		/// @brief 浮動小数点数型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept FloatingPoint = std::is_floating_point_v<Type>;

		/// @brief 符号付数値型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept Signed = std::is_signed_v<Type>;

		/// @brief スカラー型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept Scalar = std::is_scalar_v<Type>;

		/// @brief 数値型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept Arithmetic = std::is_arithmetic_v<Type>;

		/// @brief 列挙型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept Enum = std::is_enum_v<Type>;

		/// @brief トリビアルコピー可能型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept TriviallyCopyable = std::is_trivially_copyable_v<Type>;

		/// @brief 一様ランダムビットジェネレータ型のコンセプト
		/// @tparam Type 型
		template <class Type>
		concept UniformRandomBitGenerator = std::invocable<Type&> && std::unsigned_integral<std::invoke_result_t<Type&>>;
		// std::enable_if_t<std::is_invocable_v<URBG&> && std::is_unsigned_v<std::invoke_result_t<URBG&>>>* = nullptr
	}
}

# endif
