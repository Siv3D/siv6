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
# include <iostream>

namespace s3d
{
	namespace detail
	{
		struct Console_impl
		{
			void open() const;
		};
	}

	inline constexpr auto Console = detail::Console_impl();
}
