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

}

template <>
inline void std::swap(s3d::BigFloat& a, s3d::BigFloat& b) noexcept
{
	a.swap(b);
}
