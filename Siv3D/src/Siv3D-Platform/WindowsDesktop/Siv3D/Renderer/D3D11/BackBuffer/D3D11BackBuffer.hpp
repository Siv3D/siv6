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
# include <Siv3D/Windows/Windows.hpp>
# include "../Device/D3D11Device.hpp"
# include "../SwapChain/D3D11SwapChain.hpp"

namespace s3d
{
	class D3D11BackBuffer
	{
	private:

		ID3D11Device* m_device			= nullptr;
		
		ID3D11DeviceContext* m_context	= nullptr;

		IDXGISwapChain1* m_swapChain1	= nullptr;
	
	public:

		D3D11BackBuffer(const D3D11Device& device, const D3D11SwapChain& swapChain);

		~D3D11BackBuffer();
	};
}
