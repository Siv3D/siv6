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

# include <Siv3D/Array.hpp>
# include <Siv3D/BinaryReader.hpp>
# include <Siv3D/PointVector.hpp>

namespace s3d
{
	struct Vertex2D
	{
		Float2 pos;
		Float2 uv;
		Float4 color;
	};

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

		if (m_indexBuffer)
		{
			::glDeleteBuffers(1, &m_indexBuffer);
			m_indexBuffer = 0;
		}

		if (m_vertexBuffer)
		{
			::glDeleteBuffers(1, &m_vertexBuffer);
			m_vertexBuffer = 0;
		}

		if (m_vao)
		{
			::glDeleteVertexArrays(1, &m_vao);
			m_vao = 0;
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

		CheckGLError();
	}

	void CRenderer2D_GL4::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_GL4::init()");

		{
			BinaryReader shader(U"engine/shader/glsl/test.vert");

			if (!shader)
			{
				throw EngineError();
			}

			Array<char> source(shader.size());
			shader.read(source.data(), shader.size());
			source.push_back('\0');
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
			BinaryReader shader(U"engine/shader/glsl/test.frag");

			if (!shader)
			{
				throw EngineError();
			}

			Array<char> source(shader.size());
			shader.read(source.data(), shader.size());
			source.push_back('\0');
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

		CheckGLError();

		::glGenProgramPipelines(1, &m_pipeline);

		CheckGLError();

		::glGenBuffers(1, &m_vertexBuffer);
		::glGenBuffers(1, &m_indexBuffer);

		::glGenVertexArrays(1, &m_vao);

		::glBindVertexArray(m_vao);
		{
			::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			::glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * VertexBufferSize, nullptr, GL_DYNAMIC_DRAW);

			::glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 32, (GLubyte*)0);
			::glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (GLubyte*)8);
			::glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 32, (GLubyte*)16);

			::glEnableVertexAttribArray(0);
			::glEnableVertexAttribArray(1);
			::glEnableVertexAttribArray(2);

			::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
			::glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexType) * IndexBufferSize, nullptr, GL_DYNAMIC_DRAW);
		}
		::glBindVertexArray(0);

		CheckGLError();

		::glBindVertexArray(m_vao);
		::glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		{
			const Vertex2D vertices[3] =
			{
				{ Float2(-0.6f, -0.4f),  Float2(0.0f, 0.0f),  Float4(1.0f, 0.0f, 0.0f, 1.0f) },
				{ Float2(0.6f, -0.4f),  Float2(0.0f, 0.0f),  Float4(0.0f, 1.0f, 0.0f, 1.0f) },
				{ Float2(0.0f,  0.6f),  Float2(0.0f, 0.0f),  Float4(0.0f, 0.0f, 1.0f, 1.0f) }
			};

			void* pDst = ::glMapBufferRange(GL_ARRAY_BUFFER, sizeof(Vertex2D) * 0, sizeof(Vertex2D) * 3,
				GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			std::memcpy(pDst, vertices, sizeof(Vertex2D) * 3);
			::glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		{
			const uint16 indices[3] = { 0, 1, 2 };
			void* pDst = ::glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexType) * 0, sizeof(IndexType) * 3,
				GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_UNSYNCHRONIZED_BIT);
			std::memcpy(pDst, indices, sizeof(IndexType) * 3);
			::glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		}
	}

	void CRenderer2D_GL4::test_renderRectangle(const RectF&, const ColorF&)
	{
		::glUseProgramStages(m_pipeline, GL_VERTEX_SHADER_BIT, m_vsProgram);
		::glUseProgramStages(m_pipeline, GL_FRAGMENT_SHADER_BIT, m_psProgram);

		::glUseProgram(0);
		::glBindProgramPipeline(m_pipeline);

		::glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (IndexType*)(nullptr) + 0, 0);

		CheckGLError();
	}
}
