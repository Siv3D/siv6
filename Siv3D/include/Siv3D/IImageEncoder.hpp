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
# include "Blob.hpp"

namespace s3d
{
	class IImageEncoder
	{
	public:

		virtual ~IImageEncoder() = default;

		[[nodiscard]]
		virtual StringView name() const = 0;
	};
}
