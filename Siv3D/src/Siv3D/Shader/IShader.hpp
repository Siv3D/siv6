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
# include <Siv3D/Blob.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DShader
	{
	public:

		static ISiv3DShader* Create();

		virtual ~ISiv3DShader() = default;

		virtual void init() = 0;

		virtual VertexShader::IDType createVS(Blob&& blob, const Array<ConstantBufferBinding>& bindings) = 0;
		
		virtual VertexShader::IDType createVS(FilePathView path, const Array<ConstantBufferBinding>& bindings) = 0;

		virtual PixelShader::IDType createPS(Blob&& blob, const Array<ConstantBufferBinding>& bindings) = 0;

		virtual PixelShader::IDType createPS(FilePathView path, const Array<ConstantBufferBinding>& bindings) = 0;
	
		virtual void release(VertexShader::IDType handleID) = 0;

		virtual void release(PixelShader::IDType handleID) = 0;

		virtual void setVS(VertexShader::IDType handleID) = 0;

		virtual void setPS(PixelShader::IDType handleID) = 0;
	};
}
