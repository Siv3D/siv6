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

# include "CRenderer_D3D11.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Texture/ITexture.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	CRenderer_D3D11::CRenderer_D3D11() = default;

	CRenderer_D3D11::~CRenderer_D3D11()
	{
		LOG_SCOPED_TRACE(U"CRenderer_D3D11::~CRenderer_D3D11()");
	}

	void CRenderer_D3D11::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_D3D11::init()");

		HWND hWnd	= static_cast<HWND>(SIV3D_ENGINE(Window)->getHandle());
		const Size frameBufferSize = SIV3D_ENGINE(Window)->getState().frameBufferSize;
		m_device		= std::make_unique<D3D11Device>();
		m_swapChain		= std::make_unique<D3D11SwapChain>(*m_device, hWnd, frameBufferSize);
		
		SIV3D_ENGINE(Texture)->init();

		m_backBuffer = std::make_unique<D3D11BackBuffer>(*m_device, *m_swapChain);

		clear();
	}

	StringView CRenderer_D3D11::getName() const
	{
		static constexpr StringView name(U"D3D11");
		return name;
	}

	void CRenderer_D3D11::clear()
	{
		m_backBuffer->clear(ClearTarget::BackBuffer | ClearTarget::SceneMS);

		if (const Size frameBufferSize = SIV3D_ENGINE(Window)->getState().frameBufferSize;
			frameBufferSize != m_backBuffer->getBackBufferSize())
		{
			m_backBuffer->setBackBufferSize(frameBufferSize);
		}
	}

	void CRenderer_D3D11::flush()
	{

	}

	bool CRenderer_D3D11::present()
	{
		if (not m_swapChain->present())
		{
			return false;
		}

		return true;
	}

	void CRenderer_D3D11::setSceneResizeMode(const ResizeMode resizeMode)
	{
		m_backBuffer->setSceneResizeMode(resizeMode);
	}

	ResizeMode CRenderer_D3D11::getSceneResizeMode() const noexcept
	{
		return m_backBuffer->getSceneResizeMode();
	}

	void CRenderer_D3D11::setSceneBufferSize(const Size size)
	{
		m_backBuffer->setSceneBufferSize(size);
	}

	Size CRenderer_D3D11::getSceneBufferSize() const noexcept
	{
		return m_backBuffer->getSceneBufferSize();;
	}
}
