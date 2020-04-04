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
# include "PointVector.hpp"
# include "Rectangle.hpp"
# include "Window.hpp"

namespace s3d
{
	struct WindowState
	{
		Size clientSize = Window::DefaultClientSize;

		Size frameBufferSize = Window::DefaultClientSize;

		double scaling = 1.0;

		Rect bounds = Rect(0);

		bool minimized = false;

		bool maximized = false;
	};
}
