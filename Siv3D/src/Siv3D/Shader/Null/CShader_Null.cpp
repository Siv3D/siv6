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

# include "CShader_Null.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CShader_Null::CShader_Null()
	{

	}

	CShader_Null::~CShader_Null()
	{
		LOG_SCOPED_TRACE(U"CShader_Null::~CShader_Null()");
	}

	void CShader_Null::init()
	{

	}

	VertexShader::IDType CShader_Null::createVS(Blob&&, const Array<ConstantBufferBinding>&)
	{
		return VertexShader::IDType::NullAsset();
	}

	VertexShader::IDType CShader_Null::createVS(FilePathView, const Array<ConstantBufferBinding>&)
	{
		return VertexShader::IDType::NullAsset();
	}

	PixelShader::IDType CShader_Null::createPS(Blob&&, const Array<ConstantBufferBinding>&)
	{
		return PixelShader::IDType::NullAsset();
	}

	PixelShader::IDType CShader_Null::createPS(FilePathView, const Array<ConstantBufferBinding>&)
	{
		return PixelShader::IDType::NullAsset();
	}

	void CShader_Null::release(const VertexShader::IDType)
	{

	}

	void CShader_Null::release(const PixelShader::IDType)
	{

	}

	void CShader_Null::setVS(const VertexShader::IDType)
	{

	}

	void CShader_Null::setPS(const PixelShader::IDType)
	{

	}
}
