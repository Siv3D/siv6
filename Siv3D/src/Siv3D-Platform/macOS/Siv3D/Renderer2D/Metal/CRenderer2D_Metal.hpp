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
# include <Siv3D/Renderer2D/IRenderer2D.hpp>
# include <Siv3D/Renderer/Metal/CRenderer_Metal.hpp>
# import <Metal/Metal.h>
# import <QuartzCore/CAMetalLayer.h>
# include "Vertex2DBatch_Metal.hpp"

namespace s3d
{
	class CRenderer2D_Metal final : public ISiv3DRenderer2D
	{
	private:
		
		CRenderer_Metal* pRenderer = nullptr;
		id<MTLDevice> m_device = nil;
		id<MTLCommandQueue> m_commandQueue = nil;
		CAMetalLayer* m_swapchain = nullptr;
		
		
		id<MTLRenderPipelineState> m_sceneRenderPipelineState = nil;
		id<MTLRenderPipelineState> m_fullscreenTriangleRenderPipelineState = nil;
		MTLRenderPassDescriptor* m_renderPassDescriptor;
		
		
		
		Vertex2DBatch_Metal m_batches;
		Renderer2DCommand_Metal m_command;
		uint32 m_draw_indexCount = 0;

	public:

		CRenderer2D_Metal();

		~CRenderer2D_Metal() override;

		void init() override;

		void flush() override {}
		
		void flush(id<MTLCommandBuffer> commandBuffer);

		void test_renderRectangle(const RectF& rect, const ColorF& color) override;
		
		void drawFullScreenTriangle(TextureFilter textureFilter) override {}
		
		void drawFullScreenTriangle(id<MTLCommandBuffer> commandBuffer, TextureFilter textureFilter);
		
		void begin();
	};
}
