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

namespace s3d
{
	class CRenderer_D3D11 final : public ISiv3DRenderer
	{
	private:

		std::unique_ptr<D3D11Device> m_device;

		std::unique_ptr<D3D11SwapChain> m_swapChain;

		std::unique_ptr<D3D11BackBuffer> m_backBuffer;

	public:

		CRenderer_D3D11();

		~CRenderer_D3D11() override;

		void init() override;

		StringView getName() const override;

		void clear() override;

		void flush() override;

		bool present() override;

		Size getFrameBufferSize() const override;

		Size getSceneSize() const override;
	};
}
