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
# include <Siv3D/Shader/IShader.hpp>

namespace s3d
{
	class CShader_Null final : public ISiv3DShader
	{
	private:

	public:

		CShader_Null();

		~CShader_Null() override;

		void init() override;

		VertexShader::IDType createVS(Blob&& binary, const Array<ConstantBufferBinding>& bindings) override;

		VertexShader::IDType createVS(FilePathView path, const Array<ConstantBufferBinding>& bindings) override;

		PixelShader::IDType createPS(Blob&& binary, const Array<ConstantBufferBinding>& bindings) override;

		PixelShader::IDType createPS(FilePathView path, const Array<ConstantBufferBinding>& bindings) override;

		void release(VertexShader::IDType handleID) override;

		void release(PixelShader::IDType handleID) override;

		void setVS(VertexShader::IDType handleID) override;

		void setPS(PixelShader::IDType handleID) override;
	};
}
