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

		[[nodiscard]]
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

		void SetMinimumFrameBufferSize(const Size& size)
		{
			SIV3D_ENGINE(Window)->setMinimumFrameBufferSize(size);
		}
	}
}
