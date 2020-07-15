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
# include <Siv3D/Common/OpenGL.hpp>

namespace s3d
{
	CRenderer_GL4::CRenderer_GL4() = default;

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

		clear();
	}

	StringView CRenderer_GL4::getName() const
	{
		static constexpr StringView name(U"OpenGL");
		return name;
	}

	void CRenderer_GL4::clear()
	{
		::glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
		SIV3D_ENGINE(Renderer2D)->flush();
	}

	bool CRenderer_GL4::present()
	{
		//wglSwapIntervalEXT(0);

		m_wglContext.swapBuffers();

		return true;
	}

	Size CRenderer_GL4::getFrameBufferSize() const
	{
		return m_frameBufferSize;
	}

	Size CRenderer_GL4::getSceneSize() const
	{
		return m_sceneSize;
	}
}
