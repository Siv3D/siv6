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

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <GL/glew.h>
# include <GL/wglew.h>
# include <GL/GL.h>

namespace s3d
{
	class CRenderer2D_GL4 final : public ISiv3DRenderer2D
	{
	private:

		GLuint vertex_buffer = 0, vertex_shader = 0, fragment_shader = 0, program = 0;
		GLint mvp_location = 0, vpos_location = 0, vcol_location = 0;

	public:

		CRenderer2D_GL4();

		~CRenderer2D_GL4() override;

		void init() override;

		void test_renderRectangle(const RectF& rect, const ColorF& color) override;
	};
}
