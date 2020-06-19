﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/ColorF.hpp>
# include <Siv3D/FormatFloat.hpp>

namespace s3d
{
	void ColorF::_Formatter(FormatData& formatData, const ColorF& value)
	{
		Formatter(formatData, value.toVec4());
	}
}
