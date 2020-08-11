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

# include <Siv3D/Texture.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	template <>
	AssetIDWrapper<AssetHandle<Texture>>::AssetIDWrapper()
	{

	}

	template <>
	AssetIDWrapper<AssetHandle<Texture>>::~AssetIDWrapper()
	{
		LOG_INFO(U"pTexture->release({})"_fmt(m_id.value()));
	}

	Texture::Texture()
	{

	}

	Texture::Texture(const FilePathView path)
		: Texture(Image(path))
	{

	}

	Texture::Texture(const Image&)
		: AssetHandle(std::make_shared<AssetIDWrapperType>(AssetIDWrapperType::IDType{ 1 }))
	{

	}
}
