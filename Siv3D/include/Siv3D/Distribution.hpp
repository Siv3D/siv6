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

# ifdef __clang__
	# pragma clang diagnostic push
	# pragma clang diagnostic ignored "-Wshorten-64-to-32"
# endif

SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4127)
SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
# include <ThirdParty/absl/random/distributions.h>
SIV3D_DISABLE_MSVC_WARNINGS_POP()
SIV3D_DISABLE_MSVC_WARNINGS_POP()

# ifdef __clang__
	# pragma clang diagnostic pop
# endif

namespace s3d
{
	template <class IntType = int32>
	using UniformIntDistribution = absl::uniform_int_distribution<IntType>;

	template <class RealType = double>
	using UniformRealDistribution = absl::uniform_real_distribution<RealType>;

	template <class RealType = double>
	using NormalDistribution = absl::gaussian_distribution<RealType>;
}
