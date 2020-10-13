﻿//-----------------------------------------------
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
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/Blob.hpp>
# include <Siv3D/Shader.hpp>
# include <Siv3D/ShaderStatge.hpp>
# include <Siv3D/Shader/IShader.hpp>
# include <Siv3D/AssetHandleManager/AssetHandleManager.hpp>
# include "VertexShader/GL4VertexShader.hpp"
# include "PixelShader/GL4PixelShader.hpp"

namespace s3d
{
	class CShader_GL4 final : public ISiv3DShader
	{
	private:

		// VS の管理
		AssetHandleManager<VertexShader::IDType, GL4VertexShader> m_vertexShaders{ U"VertexShader" };

		// PS の管理
		AssetHandleManager<PixelShader::IDType, GL4PixelShader> m_pixelShaders{ U"PixelShader" };

		//[[nodiscard]]
		//Blob compileHLSL(FilePathView path, ShaderStage stage, StringView entryPoint, Platform::Windows::HLSLCompileOption flags = Platform::Windows::HLSLCompileOption::Default) const;

		//[[nodiscard]]
		//Blob compileHLSL(const Blob& blob, FilePathView pathHint, ShaderStage stage, StringView entryPoint, Platform::Windows::HLSLCompileOption flags = Platform::Windows::HLSLCompileOption::Default) const;

	public:

		CShader_GL4();

		~CShader_GL4() override;

		void init() override;


		VertexShader::IDType createVS(Blob&& binary, const Array<ConstantBufferBinding>& bindings) override;

		VertexShader::IDType createVS(FilePathView path, const Array<ConstantBufferBinding>& bindings) override;
		
		VertexShader::IDType createVSFromSource(const String& source, const Array<ConstantBufferBinding>& bindings);


		PixelShader::IDType createPS(Blob&& binary, const Array<ConstantBufferBinding>& bindings) override;

		PixelShader::IDType createPS(FilePathView path, const Array<ConstantBufferBinding>& bindings) override;
	
		PixelShader::IDType createPSFromSource(const String& source, const Array<ConstantBufferBinding>& bindings);


		// 指定した VS を管理から除外
		void releaseVS(VertexShader::IDType handleID) override;

		// 指定した PS を管理から除外
		void releasePS(PixelShader::IDType handleID) override;
	
		// 指定した VS を context にセット
		void setVS(VertexShader::IDType handleID) override {}

		// 指定した PS を context にセット
		void setPS(PixelShader::IDType handleID) override {}
	
		const Blob& getBinaryVS(VertexShader::IDType handleID) override;

		const Blob& getBinaryPS(PixelShader::IDType handleID) override;

		void setConstantBufferVS(uint32 slot, const ConstantBufferBase& cb) override {}

		void setConstantBufferPS(uint32 slot, const ConstantBufferBase& cb) override {}

		GLuint getVSProgram(VertexShader::IDType handleID);
		
		GLuint getPSProgram(PixelShader::IDType handleID);
		
		void setPSSamplerUniform(PixelShader::IDType handleID);
	};
}