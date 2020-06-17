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
# include <Siv3D/Image.hpp>
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
		
		for (auto& customCursor : m_customCursors)
		{
			if (customCursor.second)
			{
				::glfwDestroyCursor(customCursor.second);
				customCursor.second = nullptr;
			}
		}
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

	bool CCursor::registerCursor(const StringView name, const Image& image, const Point& hotSpot)
	{
		const String iconName(name);

		if (m_customCursors.contains(iconName))
		{
			return false;
		}
		
		Array pixels = image.asArray();
		GLFWimage cursorImage;
		cursorImage.width	= image.width();
		cursorImage.height	= image.height();
		cursorImage.pixels	= (uint8*)pixels.data();
		 
		if (GLFWcursor* cursor = ::glfwCreateCursor(&cursorImage, hotSpot.x, hotSpot.y))
		{
			m_customCursors.emplace(iconName, cursor);
			return true;
		}
		else
		{
			return false;
		}
	}

	void CCursor::requestStyle(const StringView name)
	{
		if (auto it = m_customCursors.find(String(name));
			it != m_customCursors.end())
		{
			::glfwSetCursor(m_window, it->second);
		}
	}
}
