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
# include <Siv3D/ScopeGuard.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Mat3x2.hpp>

namespace s3d
{
	struct alignas(16) VSConstants2D
	{
		Float4 transform[2];
		Float4 colorMul;
	};

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
		m_device = m_pRenderer->getDevice();
		m_commandQueue = m_pRenderer->getCommandQueue();
		m_swapchain = m_pRenderer->getSwapchain();
	
		id<MTLLibrary> defaultLibrary = [m_device newDefaultLibrary];
		id<MTLFunction> vertexFunction = [defaultLibrary newFunctionWithName:@"VS_Sprite"];
		id<MTLFunction> fragmentFunction = [defaultLibrary newFunctionWithName:@"PS_Shape"];
		
		MTLVertexDescriptor* vertexDescriptor = [MTLVertexDescriptor new];
		vertexDescriptor.attributes[0].format = MTLVertexFormatFloat2;
		vertexDescriptor.attributes[0].offset = 0;
		vertexDescriptor.attributes[0].bufferIndex = 0;
		vertexDescriptor.attributes[1].format = MTLVertexFormatFloat2;
		vertexDescriptor.attributes[1].offset = 8;
		vertexDescriptor.attributes[1].bufferIndex = 0;
		vertexDescriptor.attributes[2].format = MTLVertexFormatFloat4;
		vertexDescriptor.attributes[2].offset = 16;
		vertexDescriptor.attributes[2].bufferIndex = 0;
		vertexDescriptor.layouts[0].stride = 32;
		 
		MTLRenderPipelineDescriptor* rpd = [MTLRenderPipelineDescriptor new];
		rpd.vertexFunction = vertexFunction;
		rpd.fragmentFunction = fragmentFunction;
		rpd.colorAttachments[0].pixelFormat = m_swapchain.pixelFormat;
		rpd.vertexDescriptor = vertexDescriptor;
		m_rps = [m_device newRenderPipelineStateWithDescriptor:rpd error:NULL];
		assert(m_rps);
		
		m_batches.init(m_device);
	}

	void CRenderer2D_Metal::flush()
	{
		ScopeGuard cleanUp = [this]()
		{
			m_draw_indexCount = 0;
		};
		
		m_batches.end();
		const Size currentRenderTargetSize = SIV3D_ENGINE(Renderer)->getSceneBufferSize();

		Mat3x2 transform = Mat3x2::Identity();
		Mat3x2 screenMat = Mat3x2::Screen(currentRenderTargetSize);
		const Mat3x2 matrix = transform * screenMat;
		
		VSConstants2D cb;
		//cb[0] = Float4(matrix._11, -matrix._12, matrix._31, -matrix._32);
		//cb[1] = Float4(matrix._21, -matrix._22, 0.0f, 1.0f);
		cb.transform[0] = Float4(matrix._11, -matrix._12, matrix._31, matrix._32);
		cb.transform[1] = Float4(matrix._21, matrix._22, 0.0f, 1.0f);
		cb.colorMul = Float4(1, 1, 1, 1);
		
		@autoreleasepool {
			id<MTLCommandBuffer> buffer = [m_commandQueue commandBuffer];
			id<CAMetalDrawable> drawable = [m_swapchain nextDrawable];
			assert(drawable);

			MTLRenderPassDescriptor* pass = [MTLRenderPassDescriptor renderPassDescriptor];
			pass.colorAttachments[0].clearColor = MTLClearColorMake(0.8, 0.9, 1.0, 1);
			pass.colorAttachments[0].loadAction  = MTLLoadActionClear;
			pass.colorAttachments[0].storeAction = MTLStoreActionStore;
			pass.colorAttachments[0].texture = drawable.texture;
			id<MTLRenderCommandEncoder> encoder = [buffer renderCommandEncoderWithDescriptor:pass];

			[encoder setRenderPipelineState:m_rps];

			[encoder setVertexBuffer:m_batches.getCurrentVertexBuffer()
							  offset:0
							 atIndex:0];
			
			[encoder setVertexBytes:&cb
							 length:sizeof(VSConstants2D)
							atIndex:1];

			if (m_draw_indexCount)
			{
				[encoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
									indexCount:m_draw_indexCount
									 indexType:MTLIndexTypeUInt16
								   indexBuffer:m_batches.getCurrentIndexBuffer()
							 indexBufferOffset:0];
			}
			
			[encoder endEncoding];
			[buffer presentDrawable:drawable];
			
			__weak dispatch_semaphore_t semaphore = m_batches.getSemaphore();
			[buffer addCompletedHandler:^(id<MTLCommandBuffer>)
			{
				dispatch_semaphore_signal(semaphore);
			}];
			
			[buffer commit];
		}
	}

	void CRenderer2D_Metal::test_renderRectangle(const RectF& rect, const ColorF& _color)
	{
		constexpr Vertex2D::IndexType vertexSize = 4, indexSize = 6;
		auto [pVertex, pIndex, indexOffset] = m_batches.requestBuffer(vertexSize, indexSize, m_command);

		if (!pVertex)
		{
			return;
		}

		const Float4 color = _color.toFloat4();

		const float left = float(rect.x);
		const float right = float(rect.x + rect.w);
		const float top = float(rect.y);
		const float bottom = float(rect.y + rect.h);

		pVertex[0].set(left, top, color);
		pVertex[1].set(right, top, color);
		pVertex[2].set(left, bottom, color);
		pVertex[3].set(right, bottom, color);

		static constexpr Vertex2D::IndexType RectIndexTable[6] = { 0, 1, 2, 2, 1, 3 };

		for (Vertex2D::IndexType i = 0; i < indexSize; ++i)
		{
			*pIndex++ = (indexOffset + RectIndexTable[i]);
		}
		
		m_draw_indexCount += indexSize;
	}

	void CRenderer2D_Metal::drawFullScreenTriangle(TextureFilter textureFilter)
	{
	
	}

	void CRenderer2D_Metal::begin()
	{
		m_batches.begin();
	}
}
