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
# include <Siv3D/Common/OpenGL.hpp>

namespace s3d
{
	class CRenderer2D_GL4 final : public ISiv3DRenderer2D
	{
	private:

		GLuint m_vsProgram = 0;
		GLuint m_psProgram = 0;
		GLuint m_pipeline = 0;

		GLuint m_vao = 0;
		GLuint m_vertexBuffer = 0;
		GLuint m_indexBuffer = 0;

		using IndexType = uint16;
		static constexpr uint32 VertexBufferSize = 1023;
		static constexpr uint32 IndexBufferSize = (VertexBufferSize + 1) * 4;

	public:

		CRenderer2D_GL4();

		~CRenderer2D_GL4() override;

		void init() override;

		void test_renderRectangle(const RectF& rect, const ColorF& color) override;
	};
}
