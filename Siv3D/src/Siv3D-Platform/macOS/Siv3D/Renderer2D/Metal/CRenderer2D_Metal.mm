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

# include "CRenderer2D_Metal.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	CRenderer2D_Metal::CRenderer2D_Metal()
	{
	
	}

	CRenderer2D_Metal::~CRenderer2D_Metal()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_Metal::~CRenderer2D_Metal()");
	}

	void CRenderer2D_Metal::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_Metal::init()");
		
		m_pRenderer = dynamic_cast<CRenderer_Metal*>(SIV3D_ENGINE(Renderer));
		
		m_commandQueue = m_pRenderer->getCommandQueue();
		m_swapchain = m_pRenderer->getSwapchain();
	}

	void CRenderer2D_Metal::flush()
	{
		MTLClearColor color = MTLClearColorMake(0.8, 0.9, 1.0, 1);

		@autoreleasepool {
			id<MTLCommandBuffer> buffer = [m_commandQueue commandBuffer];
			id<CAMetalDrawable> drawable = [m_swapchain nextDrawable];
			assert(drawable);

			MTLRenderPassDescriptor* pass = [MTLRenderPassDescriptor renderPassDescriptor];
			pass.colorAttachments[0].clearColor = color;
			pass.colorAttachments[0].loadAction  = MTLLoadActionClear;
			pass.colorAttachments[0].storeAction = MTLStoreActionStore;
			pass.colorAttachments[0].texture = drawable.texture;

			id<MTLRenderCommandEncoder> encoder = [buffer renderCommandEncoderWithDescriptor:pass];

			[encoder endEncoding];
			[buffer presentDrawable:drawable];
			[buffer commit];
		}
	}

	void CRenderer2D_Metal::test_renderRectangle(const RectF&, const ColorF&)
	{

	}
}
