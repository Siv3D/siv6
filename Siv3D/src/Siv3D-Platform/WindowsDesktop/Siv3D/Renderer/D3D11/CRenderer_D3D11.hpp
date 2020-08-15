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
# include <memory>
# include <Siv3D/Common.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# include "Device/D3D11Device.hpp"
# include "SwapChain/D3D11SwapChain.hpp"
# include "BackBuffer/D3D11BackBuffer.hpp"
# include "BlendState/D3D11BlendState.hpp"
# include "RasterizerState/D3D11RasterizerState.hpp"
# include "DepthStencilState/D3D11DepthStencilState.hpp"
# include "SamplerState/D3D11SamplerState.hpp"

namespace s3d
{
	class CRenderer_D3D11 final : public ISiv3DRenderer
	{
	private:

		std::unique_ptr<D3D11Device> m_device;

		std::unique_ptr<D3D11SwapChain> m_swapChain;

		std::unique_ptr<D3D11BackBuffer> m_backBuffer;

		std::unique_ptr<D3D11BlendState> m_blendState;

		std::unique_ptr<D3D11RasterizerState> m_rasterizerState;

		std::unique_ptr<D3D11DepthStencilState> m_depthStencilState;

		std::unique_ptr<D3D11SamplerState> m_samplerState;

	public:

		CRenderer_D3D11();

		~CRenderer_D3D11() override;

		void init() override;

		StringView getName() const override;

		void clear() override;

		void flush() override;

		bool present() override;

		void setSceneResizeMode(ResizeMode resizeMode) override;

		ResizeMode getSceneResizeMode() const noexcept override;

		void setSceneBufferSize(Size size) override;

		Size getSceneBufferSize() const noexcept override;

		std::pair<float, FloatRect> getLetterboxComposition() const noexcept override;



		ID3D11Device* getDevice() const;

		ID3D11DeviceContext* getContext() const;

		D3D11BackBuffer& getBackBuffer() noexcept;

		D3D11BlendState& getBlendState() noexcept;

		D3D11RasterizerState& getRasterizerState() noexcept;

		D3D11SamplerState& getSamplerState() noexcept;
	};
}
