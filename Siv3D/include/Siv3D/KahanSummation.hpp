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
# include "Common.hpp"

namespace s3d
{
# ifdef __cpp_lib_concepts
	template <Concept::FloatingPoint FloatingPoint>
# else
	template <class FloatingPoint>
# endif
	class KahanSummation
	{
	private:

		FloatingPoint m_sum = 0;
		FloatingPoint m_err = 0;

	public:

		KahanSummation() = default;

		constexpr KahanSummation(FloatingPoint init) noexcept;

		constexpr void operator +=(FloatingPoint value) noexcept;

		[[nodiscard]]
		constexpr FloatingPoint value() const noexcept;
	};
}

# include "detail/KahanSummation.ipp"
