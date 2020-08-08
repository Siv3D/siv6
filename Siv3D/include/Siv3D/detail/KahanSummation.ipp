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
	SIV3D_CONCEPT_FLOATING_POINT_
	inline constexpr KahanSummation<Float>::KahanSummation(Float init) noexcept
		: m_sum(init)
	{
	
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline constexpr void KahanSummation<Float>::operator +=(const Float value) noexcept
	{
		const Float y = value - m_err;
		const Float t = m_sum + y;
		m_err = (t - m_sum) - y;
		m_sum = t;
	}

	SIV3D_CONCEPT_FLOATING_POINT_
	inline constexpr Float KahanSummation<Float>::value() const noexcept
	{
		return m_sum;
	}
}
