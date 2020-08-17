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
	namespace detail
	{
		static GLuint LoadShaders(const FilePath& vsFilePath, const FilePath& psFilePath)
		{
			const std::string vsSource = TextReader(vsFilePath).readAll().toUTF8();
			const std::string psSource = TextReader(psFilePath).readAll().toUTF8();

			if (vsSource.empty() || psSource.empty())
			{
				return 0;
			}

			GLuint vertexShader = ::glCreateShader(GL_VERTEX_SHADER);
			{
				const char* vsSourcePtr = vsSource.c_str();

				::glShaderSource(vertexShader, 1, &vsSourcePtr, nullptr);
				::glCompileShader(vertexShader);

				GLint status = GL_FALSE, infoLogLength = 0;
				::glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
				::glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);

				if (infoLogLength > 0)
				{
					std::string logText(infoLogLength + 1, '\0');
					::glGetShaderInfoLog(vertexShader, infoLogLength, nullptr, logText.data());
					LOG_FAIL(U"VS: {0}"_fmt(Unicode::Widen(logText)));
				}
			}

			GLuint pixelShader = ::glCreateShader(GL_FRAGMENT_SHADER);
			{
				const char* psSourcePtr = psSource.c_str();

				::glShaderSource(pixelShader, 1, &psSourcePtr, nullptr);
				::glCompileShader(pixelShader);

				GLint status = GL_FALSE, infoLogLength = 0;
				::glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &status);
				::glGetShaderiv(pixelShader, GL_INFO_LOG_LENGTH, &infoLogLength);

				if (infoLogLength > 0)
				{
					std::string logText(infoLogLength + 1, '\0');
					::glGetShaderInfoLog(pixelShader, infoLogLength, nullptr, logText.data());
					LOG_FAIL(U"PS: {0}"_fmt(Unicode::Widen(logText)));
				}
			}

			GLuint program = ::glCreateProgram();
			{
				::glAttachShader(program, vertexShader);
				::glAttachShader(program, pixelShader);
				::glLinkProgram(program);

				GLint status = GL_FALSE, infoLogLength = 0;
				::glGetProgramiv(program, GL_LINK_STATUS, &status);
				::glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

				if (infoLogLength > 0)
				{
					std::string logText(infoLogLength + 1, '\0');
					::glGetProgramInfoLog(pixelShader, infoLogLength, nullptr, logText.data());
					LOG_FAIL(U"LINK: {0}"_fmt(Unicode::Widen(logText)));
				}
			}

			::glDetachShader(program, vertexShader);
			::glDetachShader(program, pixelShader);

			::glDeleteShader(vertexShader);
			::glDeleteShader(pixelShader);

			return program;
		}
	}

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

		if (m_copyProgram)
		{
			::glDeleteProgram(m_copyProgram);
			m_copyProgram = 0;
		}



		if (m_uniformBuffer)
		{
			::glDeleteBuffers(1, &m_uniformBuffer);
			m_uniformBuffer = 0;
		}

		if (m_pipeline)
		{
			::glDeleteProgramPipelines(1, &m_pipeline);
			m_pipeline = 0;
		}

		if (m_psProgram)
		{
			::glDeleteProgram(m_psProgram);
			m_psProgram = 0;
		}

		if (m_vsProgram)
		{
			::glDeleteProgram(m_vsProgram);
			m_vsProgram = 0;
		}

		CheckOpenGLError();
	}

	void CRenderer2D_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_GL4::init()");

		pRenderer = dynamic_cast<CRenderer_GL4*>(SIV3D_ENGINE(Renderer));

		{
			BinaryReader shader(Resource(U"engine/shader/glsl/test.vert"));

			if (!shader)
			{
				throw EngineError();
			}

			Array<char> source(shader.size() + 1);
			shader.read(source.data(), shader.size());
			const char* pSource = source.data();
			m_vsProgram = ::glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &pSource);

			GLint status = GL_FALSE;
			::glGetProgramiv(m_vsProgram, GL_LINK_STATUS, &status);

			GLint logLen = 0;
			::glGetProgramiv(m_vsProgram, GL_INFO_LOG_LENGTH, &logLen);

			if (logLen > 4)
			{
				std::string log(logLen + 1, '\0');
				::glGetProgramInfoLog(m_vsProgram, logLen, &logLen, &log[0]);
				LOG_FAIL(U"❌ Vertex shader compilation failed: {0}"_fmt(Unicode::Widen(log)));
				throw EngineError();
			}

			if (status == GL_FALSE) // もしリンクに失敗していたら
			{
				::glDeleteProgram(m_vsProgram);
				m_vsProgram = 0;
				throw EngineError();
			}
		}

		{
			BinaryReader shader(Resource(U"engine/shader/glsl/test.frag"));

			if (!shader)
			{
				throw EngineError();
			}

			Array<char> source(shader.size() + 1);
			shader.read(source.data(), shader.size());
			const char* pSource = source.data();
			m_psProgram = ::glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &pSource);

			GLint status = GL_FALSE;
			::glGetProgramiv(m_psProgram, GL_LINK_STATUS, &status);

			GLint logLen = 0;
			::glGetProgramiv(m_psProgram, GL_INFO_LOG_LENGTH, &logLen);

			// ログメッセージ
			if (logLen > 4)
			{
				std::string log(logLen + 1, '\0');
				::glGetProgramInfoLog(m_psProgram, logLen, &logLen, &log[0]);
				LOG_FAIL(U"❌ Pixel shader compilation failed: {0}"_fmt(Unicode::Widen(log)));
				throw EngineError();
			}

			if (status == GL_FALSE) // もしリンクに失敗していたら
			{
				::glDeleteProgram(m_psProgram);
				m_psProgram = 0;
				throw EngineError();
			}
		}

		::glGenProgramPipelines(1, &m_pipeline);

		::glGenBuffers(1, &m_uniformBuffer);

		// Batch 管理を初期化
		if (!m_batches.init())
		{
			throw EngineError(U"GL4Vertex2DBatch::init() failed");
		}

		// full screen triangle
		{
			m_copyProgram = detail::LoadShaders(Resource(U"engine/shader/glsl/fullscreen_triangle.vert"), Resource(U"engine/shader/glsl/fullscreen_triangle.frag"));
			if (!m_copyProgram)
			{
				throw EngineError();
			}
			m_locationTexture = ::glGetUniformLocation(m_copyProgram, "Texture0");

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

		::glUseProgramStages(m_pipeline, GL_VERTEX_SHADER_BIT, m_vsProgram);
		::glUseProgramStages(m_pipeline, GL_FRAGMENT_SHADER_BIT, m_psProgram);

		::glUseProgram(0);
		::glBindProgramPipeline(m_pipeline);

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
			const uint32 vsUniformBlockBinding = 0;
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

		::glUseProgram(m_copyProgram);
		{
			::glUniform1i(m_locationTexture, 0);
			
			::glBindVertexArray(m_vertexArray);
			{
				::glBindBuffer(GL_ARRAY_BUFFER, 0);
				::glDrawArrays(GL_TRIANGLES, 0, 3);
			}
			::glBindVertexArray(0);
		}
		::glUseProgram(0);

		CheckOpenGLError();
	}
}
