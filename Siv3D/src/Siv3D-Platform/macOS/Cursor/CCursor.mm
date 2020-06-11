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

# include <Siv3D/Common.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/EngineLog.hpp>
# include "CCursor.hpp"

# import  <Cocoa/Cocoa.h>

namespace s3d
{
	namespace detail
	{
		Point CursorScreenPos_macOS()
		{
			const int32 screenHeight = [[NSScreen mainScreen] frame].size.height;
			const float scaleFactor = [[NSScreen mainScreen] backingScaleFactor];
			const float scaledHeight = (screenHeight * scaleFactor);
			const NSPoint screenPos = [NSEvent mouseLocation];
			
			return Vec2(screenPos.x * scaleFactor, scaledHeight - (screenPos.y * scaleFactor)).asPoint();
		}
	}

	CCursor::CCursor()
	{

	}

	CCursor::~CCursor()
	{
		LOG_SCOPED_TRACE(U"CCursor::~CCursor()");
	}

	void CCursor::init()
	{
		LOG_SCOPED_TRACE(U"CCursor::init()");
		
		m_window = static_cast<GLFWwindow*>(SIV3D_ENGINE(Window)->getHandle());
	}

	bool CCursor::update()
	{
		//const Point screenPos = detail::CursorScreenPos_macOS();
		double clientX, clientY;
		::glfwGetCursorPos(m_window, &clientX, &clientY);
		const Vec2 clientPos(clientX, clientY);
		
		const Vec2 frameBufferSize = SIV3D_ENGINE(Window)->getState().frameBufferSize;
		const Vec2 virtualSize = SIV3D_ENGINE(Window)->getState().virtualSize;
		const double uiScaling = frameBufferSize.x / virtualSize.x;
		
		const Point screenPos = detail::CursorScreenPos_macOS();
		
		m_state.update(clientPos.asPoint(), clientPos / uiScaling, screenPos);
		
		
		return true;
	}

	const CursorState& CCursor::getState() const noexcept
	{
		return m_state;
	}
}
