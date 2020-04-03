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
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

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

		m_hDC = ::GetDC(m_hWnd);

		if (!m_hDC)
		{
			throw EngineError(U"GetDC() failed");
		}

		const int32 pixelFormat = ::ChoosePixelFormat(m_hDC, &pixelFormatDesc);

		if (pixelFormat == 0)
		{
			throw EngineError(U"ChoosePixelFormat() failed");
		}

		if (!::SetPixelFormat(m_hDC, pixelFormat, &pixelFormatDesc))
		{
			throw EngineError(U"SetPixelFormat() failed");
		}

		m_glContext = ::wglCreateContext(m_hDC);
	}
}
