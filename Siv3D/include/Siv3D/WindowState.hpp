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
# include "WindowStyle.hpp"

namespace s3d
{
	struct WindowState
	{
		Size virtualSize = Window::DefaultClientSize;

		Size frameBufferSize = Window::DefaultClientSize;

		Size minFrameBufferSize = Size(1, 1);

		double scaling = 1.0;

		Rect bounds = Rect(0);

		WindowStyle style = WindowStyle::Fixed;

		Size frameSize = Size(0, 0);

		int32 titleBarHeight = 0;

		bool fullscreen = false;

		bool minimized = false;

		bool maximized = false;

		bool focused = true;

		bool sizeMove = false;
	};
}
