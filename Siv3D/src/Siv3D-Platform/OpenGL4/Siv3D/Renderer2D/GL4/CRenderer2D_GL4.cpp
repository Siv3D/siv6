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
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/Resource.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>

namespace s3d
{
	CRenderer2D_GL4::CRenderer2D_GL4() = default;

	CRenderer2D_GL4::~CRenderer2D_GL4()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_GL4::~CRenderer2D_GL4()");

		//////////////////////////////////////////////////
		//
		//	full screen triangle
		//
		//////////////////////////////////////////////////

		if (m_sampler)
		{
			::glDeleteSamplers(1, &m_sampler);
			m_sampler = 0;
		}

		if (m_vertexArray)
		{
			::glDeleteVertexArrays(1, &m_vertexArray);
			m_vertexArray = 0;
		}


		if (m_uniformBuffer)
		{
			::glDeleteBuffers(1, &m_uniformBuffer);
			m_uniformBuffer = 0;
		}

		CheckOpenGLError();
	}

	void CRenderer2D_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_GL4::init()");

		pRenderer = dynamic_cast<CRenderer_GL4*>(SIV3D_ENGINE(Renderer));
		pShader = dynamic_cast<CShader_GL4*>(SIV3D_ENGINE(Shader));

		m_vertexShaders << VertexShader((Resource(U"engine/shader/glsl/sprite.vert")), {});
		if (!m_vertexShaders.front())
		{
			throw EngineError();
		}

		m_pixelShaders << PixelShader(Resource(U"engine/shader/glsl/shape.frag"), {});
		if (!m_pixelShaders.front())
		{
			throw EngineError();
		}

		// パイプライン管理を初期化
		if (!m_pipeline.init())
		{
			throw EngineError(U"GL4ShaderPipeline::init() failed");
		}

		::glGenBuffers(1, &m_uniformBuffer);

		// Batch 管理を初期化
		if (!m_batches.init())
		{
			throw EngineError(U"GL4Vertex2DBatch::init() failed");
		}

		// full screen triangle
		{
			m_fstVertexShaders << VertexShader(Resource(U"engine/shader/glsl/fullscreen_triangle.vert"), {});
			if (!m_fstVertexShaders.front())
			{
				throw EngineError();
			}
			
			m_fstPixelShaders << PixelShader(Resource(U"engine/shader/glsl/fullscreen_triangle.frag"), {});
			if (!m_fstPixelShaders.front())
			{
				throw EngineError();
			}

			//m_copyProgram = detail::LoadShaders(Resource(U"engine/shader/glsl/fullscreen_triangle.vert"), Resource(U"engine/shader/glsl/fullscreen_triangle.frag"));
			//if (!m_copyProgram)
			//{
			//	throw EngineError();
			//}
			//m_locationTexture = ::glGetUniformLocation(m_copyProgram, "Texture0");

			::glGenVertexArrays(1, &m_vertexArray);
			::glBindVertexArray(m_vertexArray);

			::glGenSamplers(1, &m_sampler);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}

		CheckOpenGLError();
	}

	void CRenderer2D_GL4::flush()
	{
		ScopeGuard cleanUp = [this]()
		{
			m_batches.reset();
			m_draw_indexCount = 0;
		};

		if (m_draw_indexCount == 0)
		{
			return;
		}

		m_pipeline.setVS(pShader->getVSProgram(m_vertexShaders.front().id()));
		m_pipeline.setPS(pShader->getPSProgram(m_pixelShaders.front().id()));
		m_pipeline.use();

		const Size currentRenderTargetSize = SIV3D_ENGINE(Renderer)->getSceneBufferSize();
		::glViewport(0, 0, currentRenderTargetSize.x, currentRenderTargetSize.y);

		Mat3x2 transform = Mat3x2::Identity();
		Mat3x2 screenMat = Mat3x2::Screen(currentRenderTargetSize);
		const Mat3x2 matrix = (transform * screenMat);
		
		Float4 cb[3];
		cb[0] = Float4(matrix._11, -matrix._12, matrix._31, -matrix._32);
		cb[1] = Float4(matrix._21, -matrix._22, 0.0f, 1.0f);
		cb[2] = Float4(1, 1, 1, 1);

		{
			::glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
			::glBufferData(GL_UNIFORM_BUFFER, sizeof(Float4) * 3, cb, GL_STATIC_DRAW);
			::glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		{
			constexpr uint32 vsUniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Vertex, 0);
			::glBindBufferBase(GL_UNIFORM_BUFFER, vsUniformBlockBinding, m_uniformBuffer);
		}

		auto batchInfo = m_batches.updateBuffers(0);

		const uint32 indexCount = m_draw_indexCount;
		const uint32 startIndexLocation = batchInfo.startIndexLocation;
		const uint32 baseVertexLocation = batchInfo.baseVertexLocation;
		const Vertex2D::IndexType* pBase = 0;
		
		::glDrawElementsBaseVertex(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, (pBase + startIndexLocation), baseVertexLocation);
		batchInfo.startIndexLocation += indexCount;

		::glBindVertexArray(0);

		CheckOpenGLError();
	}

	void CRenderer2D_GL4::test_renderRectangle(const RectF& rect, const ColorF& _color)
	{
		constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
		auto [pVertex, pIndex, indexOffset] = m_batches.requestBuffer(vertexSize, indexSize, m_command);

		if (!pVertex)
		{
			return;
		}

		const Float4 color = _color.toFloat4();

		const float left = float(rect.x);
		const float right = float(rect.x + rect.w);
		const float top = float(rect.y);
		const float bottom = float(rect.y + rect.h);

		pVertex[0].set(left, top, color);
		pVertex[1].set(right, top, color);
		pVertex[2].set(left, bottom, color);
		pVertex[3].set(right, bottom, color);

		static constexpr Vertex2D::IndexType RectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };

		for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
		{
			*pIndex++ = (indexOffset + RectIndexTable[i]);
		}

		m_draw_indexCount += 6;
	}

	void CRenderer2D_GL4::drawFullScreenTriangle(const TextureFilter textureFilter)
	{
		// view port
		{
			::glBindFramebuffer(GL_FRAMEBUFFER, 0);
			auto [s, viewRect] = pRenderer->getLetterboxComposition();
			::glViewport(
				static_cast<int32>(viewRect.left),
				static_cast<int32>(viewRect.top),
				static_cast<int32>(viewRect.right),
				static_cast<int32>(viewRect.bottom));
		}

		// render states
		{
			const bool linearFilter = (textureFilter == TextureFilter::Linear);
			::glBindSampler(0, m_sampler);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST);
			::glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, linearFilter ? GL_LINEAR : GL_NEAREST);
		}

		m_pipeline.setVS(pShader->getVSProgram(m_fstVertexShaders.front().id()));
		m_pipeline.setPS(pShader->getPSProgram(m_fstPixelShaders.front().id()));
		m_pipeline.use();
		{
			pShader->setPSSamplerUniform(m_fstPixelShaders.front().id());

			::glBindVertexArray(m_vertexArray);
			{
				::glBindBuffer(GL_ARRAY_BUFFER, 0);
				::glDrawArrays(GL_TRIANGLES, 0, 3);
			}
			::glBindVertexArray(0);
		}

		CheckOpenGLError();
	}
}
