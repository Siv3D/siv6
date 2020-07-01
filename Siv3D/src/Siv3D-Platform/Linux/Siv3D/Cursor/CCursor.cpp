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
# include <Siv3D/EngineLog.hpp>
# include "CCursor.hpp"

namespace s3d
{
	CCursor::CCursor()
	{

	}

	CCursor::~CCursor()
	{
		LOG_SCOPED_TRACE(U"CCursor::~CCursor()");

		m_customCursors.clear();
	}

	void CCursor::init()
	{
		LOG_SCOPED_TRACE(U"CCursor::init()");
	}

	bool CCursor::update()
	{
		// [Siv3D ToDo][Siv3D Linux]

		return true;
	}

	const CursorState& CCursor::getState() const noexcept
	{
		return m_state;
	}

	bool CCursor::registerCursor(const StringView name, const Image& image, const Point& hotSpot)
	{
		if (m_customCursors.contains(name))
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
			m_customCursors.emplace(name, unique_resource{ cursor, CursorDeleter });
			return true;
		}
		else
		{
			return false;
		}
	}

	void CCursor::requestStyle(const StringView name)
	{
		if (auto it = m_customCursors.find(name);
			it != m_customCursors.end())
		{
			::glfwSetCursor(m_window, it->second.get());
		}
	}
}
