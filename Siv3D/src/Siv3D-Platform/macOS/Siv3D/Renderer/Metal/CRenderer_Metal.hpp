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
# include <Siv3D/Common/OpenGL.hpp>
# include <Siv3D/Renderer/IRenderer.hpp>
# import <Metal/Metal.h>
# import <QuartzCore/CAMetalLayer.h>

namespace s3d
{
	class CRenderer_Metal final : public ISiv3DRenderer
	{
	private:
		
		GLFWwindow* m_window = nullptr;

		id<MTLDevice> m_device;
		
		id<MTLCommandQueue> m_commandQueue;
		
		CAMetalLayer* m_swapchain = nullptr;
		
		Size m_frameBufferSize = Size(0, 0);
		
	public:

		CRenderer_Metal();

		~CRenderer_Metal() override;

		void init() override;

		StringView getName() const override;

		void clear() override;

		void flush() override;

		bool present() override;

		Size getFrameBufferSize() const override;

		Size getSceneSize() const override;
		
		id<MTLDevice> getDevice() const;
		
		id<MTLCommandQueue> getCommandQueue() const;
		
		CAMetalLayer* getSwapchain() const;
	};
}
