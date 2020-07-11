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
# include "ImageFormat.hpp"
# include "PixelFormat.hpp"
# include "PointVector.hpp"

namespace s3d
{
	struct ImageInfo
	{
		ImageFormat imageFormat = ImageFormat::Unknown;

		PixelFormat pixelFormat = PixelFormat::Unknown;

		Size size = Size(0, 0);

		bool isAnimated = false;
	};
}
