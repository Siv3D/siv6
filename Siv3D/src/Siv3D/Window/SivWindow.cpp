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

# include <Siv3D/Window.hpp>
# include <Siv3D/Utility.hpp>
# include <Siv3D/Error.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	namespace Window
	{
		void SetTitle(const String& title)
		{
			SIV3D_ENGINE(Window)->setWindowTitle(title);
		}

		const String& GetTitle() noexcept
		{
			return SIV3D_ENGINE(Window)->getWindowTitle();
		}

		const WindowState& GetState() noexcept
		{
			return SIV3D_ENGINE(Window)->getState();
		}

		void SetStyle(const WindowStyle style)
		{
			SIV3D_ENGINE(Window)->setStyle(style);
		}

		WindowStyle GetStyle() noexcept
		{
			return GetState().style;
		}

		void SetPos(const Point& pos)
		{
			SIV3D_ENGINE(Window)->setPos(pos);
		}

		void SetPos(const int32 x, const int32 y)
		{
			SetPos(Point(x, y));
		}

		Point GetPos() noexcept
		{
			return GetState().bounds.pos;
		}

		void Maximize()
		{
			SIV3D_ENGINE(Window)->maximize();
		}

		void Restore()
		{
			SIV3D_ENGINE(Window)->restore();
		}

		void Minimize()
		{
			SIV3D_ENGINE(Window)->minimize();
		}

		bool Resize(const Size& size)
		{
			if (!InRange(size.x, 1, 8192) || !InRange(size.y, 1, 8192))
			{
				throw Error(U"Window::Resize(): width and height must be in the range [1, 8192]");
			}

			return SIV3D_ENGINE(Window)->setVirtualSize(size);
		}

		bool Resize(const int32 width, const int32 height)
		{
			return Resize(Size(width, height));
		}

		bool ResizeFrameBuffer(const Size& size)
		{
			if (!InRange(size.x, 1, 8192) || !InRange(size.y, 1, 8192))
			{
				throw Error(U"Window::ResizeFrameBuffer(): width and height must be in the range [1, 8192]");
			}

			return SIV3D_ENGINE(Window)->setFrameBufferSize(size);
		}

		bool ResizeFrameBuffer(const int32 width, const int32 height)
		{
			return ResizeFrameBuffer(Size(width, height));
		}

		void SetMinimumFrameBufferSize(const Size& size)
		{
			SIV3D_ENGINE(Window)->setMinimumFrameBufferSize(size);
		}
	}
}
