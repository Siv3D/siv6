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

	void CRenderer_Metal::setSceneResizeMode(const ResizeMode resizeMode)
	{

	}

	ResizeMode CRenderer_Metal::getSceneResizeMode() const noexcept
	{
		return(ResizeMode::Default);
	}

	void CRenderer_Metal::setSceneBufferSize(const Size size)
	{

	}

	Size CRenderer_Metal::getSceneBufferSize() const noexcept
	{
		return m_sceneSize;
	}

	std::pair<float, FloatRect> CRenderer_Metal::getLetterboxComposition() const noexcept
	{
		const Float2 sceneSize		= m_sceneSize;
		const Float2 backBufferSize	= m_frameBufferSize;

		const float sx	= (backBufferSize.x / sceneSize.x);
		const float sy	= (backBufferSize.y / sceneSize.y);
		const float s	= Min(sx, sy);

		if (sx <= sy)
		{
			const float offsetY = ((backBufferSize.y - sceneSize.y * s) * 0.5f);
			const float bottom	= (backBufferSize.y - offsetY * 2.0f);

			return{ s, FloatRect(0.0f, offsetY, backBufferSize.x, bottom) };
		}
		else
		{
			const float offsetX = ((backBufferSize.x - sceneSize.x * s) * 0.5f);
			const float right	= (backBufferSize.x - offsetX * 2.0f);

			return{ s, FloatRect(offsetX, 0.0f, right, backBufferSize.y) };
		}
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
