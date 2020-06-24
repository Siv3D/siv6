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


# include <Siv3D/Array.hpp>
# include <Siv3D/Vertex2D.hpp>

namespace s3d
{

	class VertexBufferManager
	{
	private:
		
		// Triple buffering
		static constexpr size_t MaxInflightBuffers = 3;
		
		// MTLBuffer に格納する最大の頂点個数
		static constexpr size_t MaxVertices = 16384;
		
		// 描画する頂点データ
		Array<Vertex2D> m_vertices;
		
		dispatch_semaphore_t m_frameBoundarySemaphore = dispatch_semaphore_create(MaxInflightBuffers);
		
		size_t m_currentVertexBufferIndex = 0;
		
		// バッファ
		std::array<id<MTLBuffer>, 3> m_vertexBuffers;
		
	public:
		
		void init(id<MTLDevice> device)
		{
			for(size_t i = 0; i < MaxInflightBuffers; ++i)
			{
				m_vertexBuffers[i] = [device newBufferWithLength:(sizeof(Vertex2D) * MaxVertices)
														 options:MTLResourceStorageModeShared];
			}
		}
		
		size_t update()
		{
			// Wait until the inflight command buffer has completed its work
			dispatch_semaphore_wait(m_frameBoundarySemaphore, DISPATCH_TIME_FOREVER);
			
			++m_currentVertexBufferIndex %= MaxInflightBuffers;
			
			const size_t num_vertices = m_vertices.size();
			
			std::memcpy(m_vertexBuffers[m_currentVertexBufferIndex].contents,
				   m_vertices.data(), (sizeof(Vertex2D) * num_vertices));
			
			m_vertices.clear();
			
			return num_vertices;
		}
		
		auto getCurrentBuffer() const
		{
			return m_vertexBuffers[m_currentVertexBufferIndex];
		}
		
		dispatch_semaphore_t getSemaphore() const
		{
			return m_frameBoundarySemaphore;
		}
		
		Vertex2D* request(size_t size)
		{
			if ((m_vertices.size() + size) > MaxVertices)
			{
				return nullptr;
			}
			
			m_vertices.resize(m_vertices.size() + size);
			
			return m_vertices.data() + (m_vertices.size() - size);
		}
	};


	class CRenderer2D_Metal final : public ISiv3DRenderer2D
	{
	private:
		
		CRenderer_Metal* m_pRenderer = nullptr;
		
		id<MTLDevice> m_device;
		
		id<MTLCommandQueue> m_commandQueue;
		
		CAMetalLayer* m_swapchain = nullptr;
		
		id<MTLRenderPipelineState> m_rps;
		
		VertexBufferManager m_vertexBufferManager;

	public:

		CRenderer2D_Metal();

		~CRenderer2D_Metal() override;

		void init() override;

		void flush() override;

		void test_renderRectangle(const RectF& rect, const ColorF& color) override;
	};
}
