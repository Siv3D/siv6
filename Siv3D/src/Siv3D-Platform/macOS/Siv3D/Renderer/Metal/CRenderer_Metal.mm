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
# include <Siv3D/System.hpp>
# include <Siv3D/Window/IWindow.hpp>
# include <Siv3D/Renderer2D/Metal/CRenderer2D_Metal.hpp>
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
		
		dynamic_cast<CRenderer2D_Metal*>(SIV3D_ENGINE(Renderer2D))->begin();
	}

	void CRenderer_Metal::flush()
	{
		SIV3D_ENGINE(Renderer2D)->flush();
	}

	bool CRenderer_Metal::present()
	{
		if (!([::glfwGetCocoaWindow(m_window) occlusionState] &NSWindowOcclusionStateVisible))
		{
			System::Sleep(16);
		}
		
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

	id<MTLDevice> CRenderer_Metal::getDevice() const
	{
		return m_device;
	}

	id<MTLCommandQueue> CRenderer_Metal::getCommandQueue() const
	{
		return m_commandQueue;
	}

	CAMetalLayer* CRenderer_Metal::getSwapchain() const
	{
		return m_swapchain;
	}
}
