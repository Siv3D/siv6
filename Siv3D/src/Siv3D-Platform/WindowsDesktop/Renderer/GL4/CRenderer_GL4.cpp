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
# include <GL/glew.h>
# include <GL/GL.h>
# include <Siv3D/Error.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/FormatLiteral.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

# include <Siv3D/Cursor.hpp>

namespace s3d
{
	CRenderer_GL4::CRenderer_GL4()
	{
	
	}

	CRenderer_GL4::~CRenderer_GL4()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GL4::~CRenderer_GL4()");

		if (m_glContext)
		{
			::wglMakeCurrent(nullptr, nullptr);
			::wglDeleteContext(m_glContext);
			m_glContext = nullptr;
		}
		
		if (m_hDC)
		{
			::ReleaseDC(m_hWnd, m_hDC);
			m_hDC = nullptr;
		}
	}

	void CRenderer_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GL4::init()");

		m_hWnd = static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());

		constexpr PIXELFORMATDESCRIPTOR pixelFormatDesc =
		{
			.nSize			= sizeof(PIXELFORMATDESCRIPTOR),
			.nVersion		= 1,
			.dwFlags		= (PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER),
			.iPixelType		= PFD_TYPE_RGBA,
			.cColorBits		= 32,
			.cDepthBits		= 0,
			.cStencilBits	= 0,
			.iLayerType		= PFD_MAIN_PLANE,
		};

		LOG_TRACE(U"GetDC()");
		m_hDC = ::GetDC(m_hWnd);

		if (!m_hDC)
		{
			throw EngineError(U"GetDC() failed");
		}

		LOG_TRACE(U"ChoosePixelFormat()");
		const int32 pixelFormat = ::ChoosePixelFormat(m_hDC, &pixelFormatDesc);

		if (pixelFormat == 0)
		{
			throw EngineError(U"ChoosePixelFormat() failed");
		}

		LOG_TRACE(U"SetPixelFormat()");
		if (!::SetPixelFormat(m_hDC, pixelFormat, &pixelFormatDesc))
		{
			throw EngineError(U"SetPixelFormat() failed");
		}

		LOG_TRACE(U"wglCreateContext()");
		m_glContext = ::wglCreateContext(m_hDC);

		{
			LOG_TRACE(U"wglMakeCurrent()");
			if (!::wglMakeCurrent(m_hDC, m_glContext))
			{
				throw EngineError(U"wglMakeCurrent() failed");
			}

			LOG_TRACE(U"glewInit()");
			if (GLenum err = ::glewInit();
				err != GLEW_OK)
			{
				throw EngineError(U"glewInit() failed");
			}

			const String renderer = Unicode::Widen(reinterpret_cast<const char*>(::glGetString(GL_RENDERER)));
			const String vendor = Unicode::Widen(reinterpret_cast<const char*>(::glGetString(GL_VENDOR)));
			const String version = Unicode::Widen(reinterpret_cast<const char*>(::glGetString(GL_VERSION)));
			const String glslVersion = Unicode::Widen(reinterpret_cast<const char*>(::glGetString(GL_SHADING_LANGUAGE_VERSION)));

			GLint major = 0, minor = 0;
			::glGetIntegerv(GL_MAJOR_VERSION, &major);
			::glGetIntegerv(GL_MINOR_VERSION, &minor);

			LOG_INFO(U"renderer: {}"_fmt(renderer));
			LOG_INFO(U"vendor: {}"_fmt(vendor));
			LOG_INFO(U"version: {}"_fmt(version));
			LOG_INFO(U"glslVersion: {}"_fmt(glslVersion));
			LOG_INFO(U"GL_MAJOR_VERSION: {}"_fmt(major));
			LOG_INFO(U"GL_MINOR_VERSION: {}"_fmt(minor));

			::wglMakeCurrent(nullptr, nullptr);
		}
	}

	void CRenderer_GL4::onMainThreadStart()
	{
		LOG_SCOPED_TRACE(U"CRenderer_GL4::onMainThreadStart()");

		if (!::wglMakeCurrent(m_hDC, m_glContext))
		{
			throw EngineError(U"wglMakeCurrent() failed");
		}

		clear();
	}

	void CRenderer_GL4::clear()
	{
		::glClearColor(0.8f, 0.9f, 1.0f, 1.0f);
		::glClear(GL_COLOR_BUFFER_BIT);

		//GLint dims[4] = { 0 };
		//::glGetIntegerv(GL_VIEWPORT, dims);
		//GLint fbWidth = dims[2];
		//GLint fbHeight = dims[3];
		//LOG_TEST(U"{}x{}"_fmt(fbWidth, fbHeight));
	}

	void CRenderer_GL4::flush()
	{
		static int32 i = 0; ++i;

		::glColor3f(1.0f, 0.5f, 0.0f);

		const float x = -1.0f + (Cursor::PosRaw().x / 1200.0f * 2.0f);
		const float y = 1.0f - (Cursor::PosRaw().y / 900.0f * 2.0f);

		::glRectf(x, y, x + 0.5f, y - 0.5f);

		::glFlush();
	}

	bool CRenderer_GL4::present()
	{
		::SwapBuffers(m_hDC);

		return true;
	}
}
