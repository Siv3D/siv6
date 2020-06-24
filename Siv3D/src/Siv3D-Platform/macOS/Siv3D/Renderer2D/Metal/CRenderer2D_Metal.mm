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
# import <simd/simd.h>

# include <Siv3D/Array.hpp>
# include <Siv3D/Vertex2D.hpp>
# include <Siv3D/Mat3x2.hpp>

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
		m_device = m_pRenderer->getDevice();
		m_commandQueue = m_pRenderer->getCommandQueue();
		m_swapchain = m_pRenderer->getSwapchain();
		
		MTLCompileOptions* compileOptions = [MTLCompileOptions new];
		compileOptions.languageVersion = MTLLanguageVersion1_1;
		NSError* compileError;
		id<MTLLibrary> lib = [m_device newLibraryWithSource:
		   @"# include <metal_stdlib>\n"
			"# include <simd/simd.h>\n"
			"struct Vertex2D\n"
			"{\n"
			"simd::float2 pos;\n"
			"simd::float2 tex;\n"
			"simd::float4 color;\n"
			"};\n"
			"struct RasterizerData\n"
			"{\n"
			"	float4 clipSpacePosition [[position]];\n"
			"	float2 textureCoordinate;\n"
			"	float4 color;\n"
			"};\n"
			"using namespace metal;\n"
		"float4 StandardTransform(float2 pos, float4 transform0, float4 transform1)\n"
		"{\n"
		"	float4 result;\n"
		"	result.xy = transform0.zw + pos.x * transform0.xy + pos.y * transform1.xy;\n"
		"	result.zw = transform1.zw;\n"
		"	return result;\n"
		"}\n"
			"vertex RasterizerData v_simple(\n"
			"    constant Vertex2D* in [[buffer(0)]],\n"
			"    constant float4* transform [[buffer(1)]],\n"
			"    uint             vid [[vertex_id]])\n"
			"{\n"
			"	RasterizerData out;\n"
			"	out.clipSpacePosition = StandardTransform(in[vid].pos, transform[0], transform[1]);\n"
			"	out.textureCoordinate = in[vid].tex;\n"
			"	out.color = in[vid].color;\n"
			"	return out;\n"
			"}\n"
			"fragment float4 f_simple(\n"
			"    RasterizerData in [[stage_in]])\n"
			"{\n"
			"    return in.color;\n"
			"}\n"
		   options:compileOptions error:&compileError];
		if (!lib)
		{
			throw EngineError(U"newLibraryWithSource: failed");
		}
		
		id<MTLFunction> vs = [lib newFunctionWithName:@"v_simple"];
		assert(vs);
		id<MTLFunction> fs = [lib newFunctionWithName:@"f_simple"];
		assert(fs);

		MTLRenderPipelineDescriptor* rpd = [MTLRenderPipelineDescriptor new];
		rpd.vertexFunction = vs;
		rpd.fragmentFunction = fs;
		rpd.colorAttachments[0].pixelFormat = m_swapchain.pixelFormat;
		m_rps = [m_device newRenderPipelineStateWithDescriptor:rpd error:NULL];
		assert(m_rps);
		
		m_vertexBufferManager.init(m_device);
	}

	void CRenderer2D_Metal::flush()
	{
		const size_t num_vertices = m_vertexBufferManager.update();
		
		/*
		Array<Vertex2D> triangleVertices =
		{
			Vertex2D{Float2(20, 20), Float2(0, 0), Float4(0.5,1,1,1)},
			Vertex2D{Float2(420, 20), Float2(0, 0), Float4(1,1,1,1)},
			Vertex2D{Float2(20, 320), Float2(0, 0), Float4(1,1,1,1)},
		};//*/
		
		const Size currentRenderTargetSize = Size(800, 600);// SIV3D_ENGINE(Renderer)->getSceneSize();

		Mat3x2 transform = Mat3x2::Identity();
		Mat3x2 screenMat = Mat3x2::Screen(currentRenderTargetSize);
		const Mat3x2 matrix = transform * screenMat;
		
		alignas(16) Float4 cb[2];
		//cb[0] = Float4(matrix._11, -matrix._12, matrix._31, -matrix._32);
		//cb[1] = Float4(matrix._21, -matrix._22, 0.0f, 1.0f);
		cb[0] = Float4(matrix._11, -matrix._12, matrix._31, matrix._32);
		cb[1] = Float4(matrix._21, matrix._22, 0.0f, 1.0f);
		
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
			/*
			[encoder setVertexBytes:triangleVertices.data()
							 length:triangleVertices.size() * sizeof(Vertex2D)
							atIndex:0];
			 */
			[encoder setVertexBuffer:m_vertexBufferManager.getCurrentBuffer()
							  offset:0
							 atIndex:0];
			
			[encoder setVertexBytes:cb
							 length:sizeof(Float4) * 2
							atIndex:1];
			
			[encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:num_vertices];
			
			[encoder endEncoding];
			[buffer presentDrawable:drawable];
			
			__weak dispatch_semaphore_t semaphore = m_vertexBufferManager.getSemaphore();
			[buffer addCompletedHandler:^(id<MTLCommandBuffer>)
			{
				// GPU work is complete
				// Signal the semaphore to start the CPU work
				dispatch_semaphore_signal(semaphore);
			}];
			
			[buffer commit];
		}
	}

	void CRenderer2D_Metal::test_renderRectangle(const RectF& rect, const ColorF& _color)
	{
		Vertex2D* vtx = m_vertexBufferManager.request(6);
		
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
