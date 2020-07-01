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
# include <utility>
# include "Common.hpp"
# include "MathConstants.hpp"

namespace s3d
{
	namespace FastMath
	{
		[[nodiscard]]
		inline constexpr std::pair<float, float> SinCos(float value) noexcept;

		[[nodiscard]]
		inline constexpr std::pair<float, float> SinCos(double value) noexcept;
	}
}

# include "detail/FastMath.ipp"
