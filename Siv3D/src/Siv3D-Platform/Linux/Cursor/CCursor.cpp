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
	}

	void CCursor::init()
	{
		LOG_SCOPED_TRACE(U"CCursor::init()");
	}

	bool CCursor::update()
	{
		return true;
	}

	const CursorState& CCursor::getState() const noexcept
	{
		return m_state;
	}
}
