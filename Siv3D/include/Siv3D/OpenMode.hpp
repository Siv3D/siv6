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
# include <ThirdParty/EnumBitmask/EnumBitmask.hpp>

namespace s3d
{
	enum class OpenMode : uint32
	{
		RandomAccess	= 1 << 0,
		SequentialScan	= 1 << 1,
		Trunc			= 1 << 2,
		Append			= 1 << 3,
	};
	DEFINE_BITMASK_OPERATORS(OpenMode);
}
