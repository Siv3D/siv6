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

# include <Siv3D/DLL.hpp>
# include <Siv3D/Window.hpp>
# include <Siv3D/EngineLog.hpp>
# include "D3D11BackBuffer.hpp"

namespace s3d
{
	D3D11BackBuffer::D3D11BackBuffer(const D3D11Device& device, const D3D11SwapChain& swapChain)
		: m_device(device.getDevice())
		, m_context(device.getContext())
		, m_swapChain1(swapChain.getSwapChain1())
	{
		LOG_SCOPED_TRACE(U"D3D11BackBuffer::D3D11BackBuffer()");

		// バックバッファのサイズを取得
		{
			DXGI_SWAP_CHAIN_DESC1 desc = {};
			m_swapChain1->GetDesc1(&desc);
			//m_backBuffer.size.set(desc.Width, desc.Height);
			//LOG_TRACE(U"D3D11RenderTarget::m_backBuffer.size = {}"_fmt(m_backBuffer.size));
		}
	}

	D3D11BackBuffer::~D3D11BackBuffer()
	{

	}
}
