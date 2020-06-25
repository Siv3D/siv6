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
		id<MTLFunction> vertexFunction = [defaultLibrary newFunctionWithName:@"v_simple"];
		id<MTLFunction> fragmentFunction = [defaultLibrary newFunctionWithName:@"f_simple"];
		 
		MTLRenderPipelineDescriptor* rpd = [MTLRenderPipelineDescriptor new];
		rpd.vertexFunction = vertexFunction;
		rpd.fragmentFunction = fragmentFunction;
		rpd.colorAttachments[0].pixelFormat = m_swapchain.pixelFormat;
		m_rps = [m_device newRenderPipelineStateWithDescriptor:rpd error:NULL];
		assert(m_rps);
		
		m_batches.init(m_device);
	}

	void CRenderer2D_Metal::flush()
	{
		const size_t num_vertices = m_batches.update();
		const Size currentRenderTargetSize = Size(800, 600);// SIV3D_ENGINE(Renderer)->getSceneSize();

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

			[encoder setVertexBuffer:m_batches.getCurrentBuffer()
							  offset:0
							 atIndex:0];
			
			[encoder setVertexBytes:&cb
							 length:sizeof(VSConstants2D)
							atIndex:1];
			
			[encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:num_vertices];
			
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
		Vertex2D* vtx = m_batches.request(6);
		
		if (!vtx)
		{
			return;
		}
		
		const Float4 color = _color.toFloat4();
		const float left = float(rect.x);
		const float right = float(rect.x + rect.w);
		const float top = float(rect.y);
		const float bottom = float(rect.y + rect.h);

		vtx[0].set(left, top, color);
		vtx[1].set(right, top, color);
		vtx[2].set(left, bottom, color);
		vtx[3].set(left, bottom, color);
		vtx[4].set(right, top, color);
		vtx[5].set(right, bottom, color);
	}
}
