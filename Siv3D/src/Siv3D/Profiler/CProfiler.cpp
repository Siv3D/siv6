﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/String.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Time.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "CProfiler.hpp"

namespace s3d
{
	void CProfiler::init()
	{
		LOG_SCOPED_TRACE(U"CProfiler::init()");

		m_fpsTimestampMillisec = Time::GetMillisec();
	}

	bool CProfiler::beginFrame()
	{
		// FPS
		{
			if (const int64 timestampMillisec = Time::GetMillisec();
				(timestampMillisec - m_fpsTimestampMillisec) < 1000)
			{
				++m_fpsCount;
			}
			else
			{
				m_currentFPS = m_fpsCount;
				m_fpsCount = 1;
				m_fpsTimestampMillisec = timestampMillisec;
			}
		}

		return true;
	}

	void CProfiler::endFrame()
	{

	}

	int32 CProfiler::getFPS() const noexcept
	{
		return m_currentFPS;
	}

	String CProfiler::getSimpleStatistics() const
	{
		const Size frameBufferSize = SIV3D_ENGINE(Window)->getState().frameBufferSize;
		const Size sceneSize(800, 600);// = Scene::Size();
		return U"{} | {} FPS | F {}x{} | S {}x{}"_fmt(
			U"OpenGL",
			m_currentFPS,
			frameBufferSize.x, frameBufferSize.y,
			sceneSize.x, sceneSize.y);
	}
}