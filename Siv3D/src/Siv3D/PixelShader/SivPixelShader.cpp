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

# include <Siv3D/PixelShader.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<PixelShader>>::AssetIDWrapper()
	{

	}

	template <>
	AssetIDWrapper<AssetHandle<PixelShader>>::~AssetIDWrapper()
	{
		LOG_INFO(U"pShader->releasePS({})"_fmt(m_id.value()));
	}

	PixelShader::PixelShader()
	{

	}

	PixelShader::PixelShader(const FilePathView path, const Array<ConstantBufferBinding>& bindings)
		: AssetHandle(std::make_shared<AssetIDWrapperType>(AssetIDWrapperType::IDType{ 1 }))
	{

	}
}
