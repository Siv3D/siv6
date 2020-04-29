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
	[[nodiscard]]
	inline uint16 SwapEndian(uint16 value) noexcept;

	[[nodiscard]]
	inline uint32 SwapEndian(uint32 value) noexcept;

	[[nodiscard]]
	inline uint64 SwapEndian(uint64 value) noexcept;
}

# include "detail/Endian.ipp"
