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
# include <Siv3D/Array.hpp>
# include <Siv3D/Vertex2D.hpp>
# import <Metal/Metal.h>

namespace s3d
{
	class Vertex2DBatch_Metal
	{
	private:

		static constexpr size_t MaxInflightBuffers = 3;

		static constexpr size_t MaxVertices = 16384;

		Array<Vertex2D> m_vertices;
		
		dispatch_semaphore_t m_frameBoundarySemaphore = dispatch_semaphore_create(MaxInflightBuffers);
		
		size_t m_currentVertexBufferIndex = 0;

		std::array<id<MTLBuffer>, 3> m_vertexBuffers;
		
	public:
		
		void init(id<MTLDevice> device);
		
		size_t update();
		
		id<MTLBuffer> getCurrentBuffer() const;
		
		dispatch_semaphore_t getSemaphore() const;
		
		Vertex2D* request(size_t size);
	};
}
