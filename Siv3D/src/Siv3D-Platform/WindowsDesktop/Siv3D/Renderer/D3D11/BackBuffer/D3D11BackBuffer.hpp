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
# include <Siv3D/Common/D3D11.hpp>
# include <Siv3D/Scene.hpp>
# include <ThirdParty/EnumBitmask/EnumBitmask.hpp>
# include "../Device/D3D11Device.hpp"
# include "../SwapChain/D3D11SwapChain.hpp"
# include "D3D11InternalTexture2D.hpp"

namespace s3d
{
	enum class ClearTarget
	{
		BackBuffer	= 1 << 0,
		
		SceneMS		= 1 << 1,
		
		Scene		= 1 << 2,

		All			= (BackBuffer | SceneMS | Scene),
	};
	DEFINE_BITMASK_OPERATORS(ClearTarget);

	class D3D11BackBuffer
	{
	private:

		ID3D11Device* m_device			= nullptr;
		
		ID3D11DeviceContext* m_context	= nullptr;

		IDXGISwapChain1* m_swapChain1	= nullptr;

		uint32 m_sampleCount			= 4;

		ResizeMode m_sceneResizeMode	= ResizeMode::Default;

		Size m_sceneSize				= Scene::DefaultSceneSize;
	
		D3D11InternalTexture2D m_backBuffer;

		D3D11InternalTexture2D m_sceneBufferMS;

		D3D11InternalTexture2D m_sceneBuffer;

		ColorF m_letterboxColor				= Palette::DefaultLetterbox;
		
		ColorF m_backgroundColor			= Palette::DefaultBackground;

		TextureFilter m_sceneTextureFilter	= Scene::DefaultFilter;

		// 全てのレンダーターゲットを解除
		void unbindAllRenderTargets();

		void updateSceneSize();

	public:

		D3D11BackBuffer(const D3D11Device& device, const D3D11SwapChain& swapChain);

		~D3D11BackBuffer();

		void clear(ClearTarget clearTargets);

		//////////////////////////////////////////////////
		//
		//	LetterboxColor
		//
		//////////////////////////////////////////////////

		void setLetterboxColor(const ColorF& color) noexcept;

		[[nodiscard]]
		const ColorF& getLetterBoxColor() const noexcept;

		//////////////////////////////////////////////////
		//
		//	BackgroundColor
		//
		//////////////////////////////////////////////////

		void setBackgroundColor(const ColorF& color) noexcept;

		[[nodiscard]]
		const ColorF& getBackgroundColor() const noexcept;

		//////////////////////////////////////////////////
		//
		//	SceneTextureFilter
		//
		//////////////////////////////////////////////////

		void setSceneTextureFilter(TextureFilter textureFilter) noexcept;

		[[nodiscard]]
		TextureFilter getSceneTextureFilter() const noexcept;

		//////////////////////////////////////////////////
		//
		//	SceneResizeMode
		//
		//////////////////////////////////////////////////

		void setSceneResizeMode(ResizeMode resizeMode);

		[[nodiscard]]
		ResizeMode getSceneResizeMode() const noexcept;

		//////////////////////////////////////////////////
		//
		//	SceneSize
		//
		//////////////////////////////////////////////////

		void setSceneBufferSize(Size size);

		[[nodiscard]]
		const Size& getSceneBufferSize() const;

		//////////////////////////////////////////////////
		//
		//	BackBuffer
		//
		//////////////////////////////////////////////////

		void setBackBufferSize(Size backBufferSize);

		[[nodiscard]]
		const Size& getBackBufferSize() const;
	};
}
