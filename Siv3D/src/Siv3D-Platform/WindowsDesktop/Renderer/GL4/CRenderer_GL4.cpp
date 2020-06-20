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

# include "CRenderer_GL4.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <GL/glew.h>
# include <GL/wglew.h>
# include <GL/GL.h>

namespace s3d
{
	CRenderer_GL4::CRenderer_GL4()
	{
	
	}

	CRenderer_GL4::~CRenderer_GL4()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GL4::~CRenderer_GL4()");

		m_wglContext.destroy();
	}

	void CRenderer_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GL4::init()");

		m_hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());

		m_wglContext.init(m_hWnd);
	}

	void CRenderer_GL4::onMainThreadStart()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GL4::onMainThreadStart()");

		m_wglContext.makeCurrent();

		SIV3D_ENGINE(Renderer2D)->init();

		clear();
	}

	void CRenderer_GL4::clear()
	{
		::glClearColor(0.8f, 0.9f, 1.0f, 1.0f);
		::glClear(GL_COLOR_BUFFER_BIT);

		const auto& windowState = SIV3D_ENGINE(Window)->getState();
		const Size newFrameBufferSize = windowState.frameBufferSize;

		if (m_frameBufferSize != newFrameBufferSize)
		{
			LOG_VERBOSE(U"CRenderer_GL4::clear(): Frame buffer size: {}"_fmt(newFrameBufferSize));
			m_frameBufferSize = newFrameBufferSize;
			::glViewport(0, 0, m_frameBufferSize.x, m_frameBufferSize.y);

			if (windowState.sizeMove)
			{
				::Sleep(100);
			}
		}
	}

	void CRenderer_GL4::flush()
	{
		::glFlush();
	}

	bool CRenderer_GL4::present()
	{
		//wglSwapIntervalEXT(0);

		m_wglContext.swapBuffers();

		return true;
	}

	void CRenderer_GL4::test_renderRectangle(const RectF& rect, const ColorF& color)
	{
		::glColor4f(static_cast<float>(color.r),
					static_cast<float>(color.g),
					static_cast<float>(color.b),
					static_cast<float>(color.a));

		const double left = rect.x / (m_frameBufferSize.x * 0.5) - 1.0;
		const double right = (rect.x + rect.w) / (m_frameBufferSize.x * 0.5) - 1.0;
		const double top = -(rect.y / (m_frameBufferSize.y * 0.5)) + 1.0;
		const double bottom = -((rect.y + rect.h) / (m_frameBufferSize.y * 0.5)) + 1.0;

		::glRectf(static_cast<float>(left),
				static_cast<float>(top),
				static_cast<float>(right),
				static_cast<float>(bottom));
	}
}
