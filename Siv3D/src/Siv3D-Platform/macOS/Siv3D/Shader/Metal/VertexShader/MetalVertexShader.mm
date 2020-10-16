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

# include <Siv3D/EngineLog.hpp>
# include <Siv3D/ShaderStatge.hpp>
# include "MetalVertexShader.hpp"

namespace s3d
{
	MetalVertexShader::MetalVertexShader(Null)
	{
		m_initialized = true;
	}

	MetalVertexShader::MetalVertexShader(id<MTLLibrary> library, const StringView name)
	{
		const std::string nameUTF8 = name.toUTF8();
		NSString* nameNS = [NSString stringWithUTF8String:nameUTF8.c_str()];
		m_vsFunction = [library newFunctionWithName:nameNS];
		
		m_initialized = (m_vsFunction != nil);
	}

	MetalVertexShader::~MetalVertexShader()
	{

	}
/*
	GL4VertexShader::GL4VertexShader(const StringView source, const Array<ConstantBufferBinding>& bindings)
	{
		// 頂点シェーダプログラムを作成
		{
			const std::string sourceUTF8 = source.toUTF8();
			const char* pSource = sourceUTF8.c_str();
			m_vsProgram = ::glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &pSource);
		}

		GLint status = GL_FALSE;
		::glGetProgramiv(m_vsProgram, GL_LINK_STATUS, &status);

		GLint logLen = 0;
		::glGetProgramiv(m_vsProgram, GL_INFO_LOG_LENGTH, &logLen);

		// ログメッセージ
		if (logLen > 4)
		{
			std::string log(logLen + 1, '\0');
			::glGetProgramInfoLog(m_vsProgram, logLen, &logLen, &log[0]);
			LOG_FAIL(U"❌ Vertex shader compilation failed: {0}"_fmt(Unicode::Widen(log)));
		}

		if (status == GL_FALSE) // もしリンクに失敗していたら
		{
			::glDeleteProgram(m_vsProgram);
			m_vsProgram = 0;
		}

		if (m_vsProgram)
		{
			setUniformBlockBindings(bindings);
		}

		m_initialized = (m_vsProgram != 0);
	}
*/
	bool MetalVertexShader::isInitialized() const noexcept
	{
		return m_initialized;
	}

	const Blob& MetalVertexShader::getBinary() const noexcept
	{
		return m_binary;
	}

	id<MTLFunction> MetalVertexShader::getFunction() const
	{
		return m_vsFunction;
	}

/*
	GLint GL4VertexShader::getProgram() const
	{
		return m_vsProgram;
	}

	void GL4VertexShader::setUniformBlockBinding(const StringView name, const GLuint index)
	{
		const GLuint blockIndex = ::glGetUniformBlockIndex(m_vsProgram, name.narrow().c_str());

		if (blockIndex == GL_INVALID_INDEX)
		{
			LOG_FAIL(U"Uniform block `{}` not found"_fmt(name));
			return;
		}

		const GLuint uniformBlockBinding = Shader::Internal::MakeUniformBlockBinding(ShaderStage::Vertex, index);

		LOG_TRACE(U"Uniform block `{}`: binding = VS_{} ({})"_fmt(name, index, uniformBlockBinding));

		::glUniformBlockBinding(m_vsProgram, blockIndex, uniformBlockBinding);
	}

	void GL4VertexShader::setUniformBlockBindings(const Array<ConstantBufferBinding>& bindings)
	{
		for (const auto& binding : bindings)
		{
			setUniformBlockBinding(binding.name, binding.index);
		}
	}
 */
}
