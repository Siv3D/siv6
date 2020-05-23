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
# include "FormatData.hpp"

//SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4127)
//SIV3D_DISABLE_MSVC_WARNINGS_PUSH(4244)
# include <ThirdParty/absl/numeric/int128.h>
//SIV3D_DISABLE_MSVC_WARNINGS_POP()
//SIV3D_DISABLE_MSVC_WARNINGS_POP()

namespace s3d
{
	using int128 = absl::int128;

	using uint128 = absl::uint128;

	void Formatter(FormatData& formatData, int128 value);

	void Formatter(FormatData& formatData, uint128 value);
}
