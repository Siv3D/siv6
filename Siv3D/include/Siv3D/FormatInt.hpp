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
# include "Fwd.hpp"

namespace s3d
{
	[[nodiscard]]
	String ToString(const int8 value);

	[[nodiscard]]
	String ToString(const uint8 value);

	[[nodiscard]]
	String ToString(const int16 value);

	[[nodiscard]]
	String ToString(const uint16 value);

	[[nodiscard]]
	String ToString(const int32 value);

	[[nodiscard]]
	String ToString(const uint32 value);

	[[nodiscard]]
	String ToString(const long value);

	[[nodiscard]]
	String ToString(const unsigned long value);

	[[nodiscard]]
	String ToString(const long long value);

	[[nodiscard]]
	String ToString(const unsigned long long value);
}
