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
# include <Siv3D/VertexShader.hpp>
# include <Siv3D/PixelShader.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Renderer/GL4/CRenderer_GL4.hpp>
# include <Siv3D/Shader/GL4/CShader_GL4.hpp>
# include <Siv3D/Common/OpenGL.hpp>
# include "GL4Vertex2DBatch.hpp"

namespace s3d
{
	class GL4Renderer2DCommand {};

	struct GL4VSConstants2D
	{
		Float4 transform[2];

		Float4 colorMul;
	};

	class GL4ShaderPipeline
	{
	private:

		GLuint m_pipeline = 0;

	public:

		GL4ShaderPipeline() = default;

		~GL4ShaderPipeline()
		{
			if (m_pipeline)
			{
				::glDeleteProgramPipelines(1, &m_pipeline);
				m_pipeline = 0;
			}
		}

		bool init()
		{
			::glGenProgramPipelines(1, &m_pipeline);

			return m_pipeline != 0;
		}

		void setVS(GLuint vsProgramHandle)
		{
			::glUseProgramStages(m_pipeline, GL_VERTEX_SHADER_BIT, vsProgramHandle);
		}

		void setPS(GLuint psProgramHandle)
		{
			::glUseProgramStages(m_pipeline, GL_FRAGMENT_SHADER_BIT, psProgramHandle);
		}

		void use()
		{
			::glUseProgram(0);
			::glBindProgramPipeline(m_pipeline);
		}
	};

	class CRenderer2D_GL4 final : public ISiv3DRenderer2D
	{
	private:

		CRenderer_GL4* pRenderer = nullptr;
		CShader_GL4* pShader = nullptr;

		Array<VertexShader> m_vertexShaders;
		Array<PixelShader> m_pixelShaders;
		GL4ShaderPipeline m_pipeline;
		ConstantBuffer<GL4VSConstants2D> m_vsConstants2D;

		GL4Vertex2DBatch m_batches;
		GL4Renderer2DCommand m_command;
		uint32 m_draw_indexCount = 0;

		//////////////////////////////////////////////////
		//
		//	full screen triangle
		//
		//////////////////////////////////////////////////

		Array<VertexShader> m_fstVertexShaders;
		Array<PixelShader> m_fstPixelShaders;
		GLuint m_vertexArray		= 0;
		GLuint m_sampler			= 0;

	public:

		CRenderer2D_GL4();

		~CRenderer2D_GL4() override;

		void init() override;

		void flush() override;

		void test_renderRectangle(const RectF& rect, const ColorF& color) override;

		void drawFullScreenTriangle(TextureFilter textureFilter) override;
	};
}
