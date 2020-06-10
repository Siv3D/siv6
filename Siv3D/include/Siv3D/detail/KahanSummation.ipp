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
# ifdef __cpp_lib_concepts
	template <Concept::FloatingPoint FloatingPoint>
# else
	template <class FloatingPoint>
# endif
	inline constexpr KahanSummation<FloatingPoint>::KahanSummation(FloatingPoint init) noexcept
		: m_sum(init)
	{
	
	}

# ifdef __cpp_lib_concepts
	template <Concept::FloatingPoint FloatingPoint>
# else
	template <class FloatingPoint>
# endif
	inline constexpr void KahanSummation<FloatingPoint>::operator +=(const FloatingPoint value) noexcept
	{
		const FloatingPoint y = value - m_err;
		const FloatingPoint t = m_sum + y;
		m_err = (t - m_sum) - y;
		m_sum = t;
	}

# ifdef __cpp_lib_concepts
	template <Concept::FloatingPoint FloatingPoint>
# else
	template <class FloatingPoint>
# endif
	inline constexpr FloatingPoint KahanSummation<FloatingPoint>::value() const noexcept
	{
		return m_sum;
	}
}
