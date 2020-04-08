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
		template <class Type>
		concept Integral = std::is_integral_v<Type>;

		template <class Type>
		concept SignedIntegral = std::integral<Type> && (Type(-1) < Type(0));

		template <class Type>
		concept UnsignedIntegral = std::integral<Type> && !SignedIntegral<Type>;

		template <class Type>
		concept FloatingPoint = std::is_floating_point_v<Type>;

		template <class Type>
		concept Scalar = std::is_scalar_v<Type>;

		template <class Type>
		concept Arithmetic = std::is_arithmetic_v<Type>;

		template <class Type>
		concept Enum = std::is_enum_v<Type>;
	}
}

# endif
