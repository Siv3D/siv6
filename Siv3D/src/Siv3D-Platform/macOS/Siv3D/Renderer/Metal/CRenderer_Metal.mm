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

# include "CRenderer_Metal.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/WindowState.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# import <QuartzCore/CAMetalLayer.h>

namespace s3d
{
	CRenderer_Metal::CRenderer_Metal()
	{
	
	}

	CRenderer_Metal::~CRenderer_Metal()
	{
		LOG_SCOPED_TRACE(U"CRenderer_Metal::~CRenderer_Metal()");
	}

	void CRenderer_Metal::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer_Metal::init()");
		
		m_window = static_cast<GLFWwindow*>(SIV3D_ENGINE(Window)->getHandle());

		m_device = MTLCreateSystemDefaultDevice();
		
		if (!m_device)
		{
			throw EngineError(U"MTLCreateSystemDefaultDevice() failed");
		}
		
		m_commandQueue = [m_device newCommandQueue];
		
		m_swapchain = [CAMetalLayer layer];
		m_swapchain.device		= m_device;
		m_swapchain.pixelFormat	= MTLPixelFormatBGRA8Unorm;
		
		NSWindow* nswin = ::glfwGetCocoaWindow(m_window);
		nswin.contentView.layer			= m_swapchain;
		nswin.contentView.wantsLayer	= YES;
		
		clear();
	}

	StringView CRenderer_Metal::getName() const
	{
		static constexpr StringView name(U"Metal");
		return name;
	}	

	void CRenderer_Metal::clear()
	{
		const auto& windowState = SIV3D_ENGINE(Window)->getState();
		const Size newFrameBufferSize = windowState.frameBufferSize;

		if (m_frameBufferSize != newFrameBufferSize)
		{
			LOG_VERBOSE(U"CRenderer_Metal::clear(): Frame buffer size: {}"_fmt(newFrameBufferSize));
			m_frameBufferSize = newFrameBufferSize;

			if (windowState.sizeMove)
			{
				// sleep
			}
		}
		
		MTLClearColor color = MTLClearColorMake(0.8, 0.9, 1.0, 1);
		
		@autoreleasepool {
			id<CAMetalDrawable> drawable = [m_swapchain nextDrawable];
			assert(drawable);
			
            MTLRenderPassDescriptor* pass = [MTLRenderPassDescriptor renderPassDescriptor];
            pass.colorAttachments[0].clearColor = color;
            pass.colorAttachments[0].loadAction  = MTLLoadActionClear;
            pass.colorAttachments[0].storeAction = MTLStoreActionStore;
            pass.colorAttachments[0].texture = drawable.texture;
			
            id<MTLCommandBuffer> buffer = [m_commandQueue commandBuffer];
            id<MTLRenderCommandEncoder> encoder = [buffer renderCommandEncoderWithDescriptor:pass];

            [encoder endEncoding];
            [buffer presentDrawable:drawable];
            [buffer commit];
		}
	}

	void CRenderer_Metal::flush()
	{
		SIV3D_ENGINE(Renderer2D)->flush();
	}

	bool CRenderer_Metal::present()
	{
		return true;
	}

	Size CRenderer_Metal::getFrameBufferSize() const
	{
		return m_frameBufferSize;
	}

	Size CRenderer_Metal::getSceneSize() const
	{
		return Size(0, 0);
	}
}
