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

# include "CRenderer2D_D3D11.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	CRenderer2D_D3D11::CRenderer2D_D3D11() = default;

	CRenderer2D_D3D11::~CRenderer2D_D3D11()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_D3D11::~CRenderer2D_D3D11()");
	}

	void CRenderer2D_D3D11::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_D3D11::init()");

		pRenderer	= dynamic_cast<CRenderer_D3D11*>(SIV3D_ENGINE(Renderer));
		m_device	= pRenderer->getDevice();
		m_context	= pRenderer->getContext();
	}

	void CRenderer2D_D3D11::flush()
	{
		Size currentRenderTargetSize = Size(800, 600);

		D3D11_VIEWPORT viewport;
		viewport.MinDepth	= 0.0f;
		viewport.MaxDepth	= 1.0f;
		viewport.TopLeftX	= 0;
		viewport.TopLeftY	= 0;
		viewport.Width		= static_cast<float>(currentRenderTargetSize.x);
		viewport.Height		= static_cast<float>(currentRenderTargetSize.y);
		m_context->RSSetViewports(1, &viewport);


	}

	void CRenderer2D_D3D11::test_renderRectangle(const RectF&, const ColorF&)
	{

	}

	void CRenderer2D_D3D11::drawFullScreenTriangle(const TextureFilter textureFilter)
	{
		// view port
		{
			const auto [s, viewRect] = pRenderer->getLetterboxComposition();
			const CD3D11_VIEWPORT viewport{
				viewRect.left, viewRect.top,
				viewRect.right, viewRect.bottom };
			m_context->RSSetViewports(1, &viewport);
		}

		// render states
		{
			SamplerState samplerState = SamplerState::Default2D;
			samplerState.min = samplerState.mag = samplerState.mip = textureFilter;
			
			pRenderer->getSamplerState().setPS(0, samplerState);
			pRenderer->getBlendState().set(BlendState::Opaque);
			pRenderer->getRasterizerState().set(RasterizerState::Default2D);
		}
		
		// shaders
		//detail::SetVS(m_standardVS->fullscreen_triangle_draw);
		//detail::SetPS(m_standardPS->fullscreen_triangle_draw);

		// draw null vertex buffer
		m_context->IASetVertexBuffers(0, 0, nullptr, nullptr, nullptr);
		m_context->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
		m_context->IASetInputLayout(nullptr);
		//m_context->Draw(3, 0);

		//Siv3DEngine::Get<ISiv3DProfiler>()->reportDrawcalls(1, 1);
	}
}
