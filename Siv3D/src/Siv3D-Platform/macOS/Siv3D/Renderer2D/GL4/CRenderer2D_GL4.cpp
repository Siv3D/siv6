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

# include "CRenderer2D_GL4.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	inline void CheckGLError()
	{
		size_t limitter = 0;

		GLenum err;

		while ((err = glGetError()) != GL_NO_ERROR)
		{
			LOG_ERROR(U"OpenGL Error: 0x{:x}"_fmt(err));

			if (++limitter > 30)
			{
				LOG_ERROR(U"OpenGL error report interrupted.");
				break;
			}
		}
	}

	CRenderer2D_GL4::CRenderer2D_GL4()
	{
	
	}

	CRenderer2D_GL4::~CRenderer2D_GL4()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_GL4::~CRenderer2D_GL4()");

		CheckGLError();
	}

	void CRenderer2D_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_GL4::init()");

		CheckGLError();
	}

	void CRenderer2D_GL4::test_renderRectangle(const RectF&, const ColorF&)
	{

	}
}
