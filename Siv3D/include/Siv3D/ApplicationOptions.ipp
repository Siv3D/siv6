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
	namespace detail
	{
		int EnableDebugHeapManager(bool) noexcept;
		int EnableHeadlessMode(bool) noexcept;
		int EnableStdErr(bool) noexcept;
		int EnableTest(bool) noexcept;
	}
}
