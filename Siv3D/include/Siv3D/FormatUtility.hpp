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
	template <class Type>
	[[nodiscard]]
	inline String Pad(const Type& value, const std::pair<int32, char32>& padding);
}

# include "detail/FormatUtility.ipp"
