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
# include <limits>
# include <cmath>
# include "Common.hpp"
# include "Concepts.hpp"

namespace s3d
{
	/// <summary>
	/// 表現できる最大の数値
	/// </summary>
	template <class Type>
	constexpr Type Largest = std::numeric_limits<Type>::max();

	/// <summary>
	/// 表現できる最小の数値
	/// </summary>
	template <class Type>
	constexpr Type Smallest = std::numeric_limits<Type>::lowest();

	/// <summary>
	/// 正の無限大
	/// </summary>
# if __cpp_lib_concepts
	template <Concept::FloatingPoint FloatingPoint>
# else 
	template <class FloatingPoint>
# endif
	constexpr FloatingPoint Inf = std::numeric_limits<FloatingPoint>::infinity();

	/// <summary>
	/// qNaN
	/// </summary>
# if __cpp_lib_concepts
	template <Concept::FloatingPoint FloatingPoint>
# else 
	template <class FloatingPoint>
# endif
	constexpr FloatingPoint QNaN = std::numeric_limits<FloatingPoint>::quiet_NaN();

	/// <summary>
	/// sNaN
	/// </summary>
# if __cpp_lib_concepts
	template <Concept::FloatingPoint FloatingPoint>
# else 
	template <class FloatingPoint>
# endif
	constexpr FloatingPoint SNaN = std::numeric_limits<FloatingPoint>::signaling_NaN();

	/// <summary>
	/// 数値が非数 (NaN) であるかを示します。
	/// </summary>
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 数値が非数 (NaN) である場合 true, それ以外の場合は false
	/// </returns>
	template <class Type>
	[[nodiscard]]
	inline bool IsNaN(Type value) noexcept;

	/// <summary>
	/// 数値が有限値であるかを示します。
	/// </summary>
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 数値が有限値である場合 true, それ以外の場合は false
	/// </returns>
	template <class Type>
	[[nodiscard]]
	inline bool IsFinite(Type value) noexcept;

	/// <summary>
	/// 数値が無限であるかを示します。
	/// </summary>
	/// <param name="value">
	/// 数値
	/// </param>
	/// <returns>
	/// 数値が無限である場合 true, それ以外の場合は false
	/// </returns>
	template <class Type>
	[[nodiscard]]
	inline bool IsInfinity(Type value) noexcept;
}

# include "detail/Number.ipp"
