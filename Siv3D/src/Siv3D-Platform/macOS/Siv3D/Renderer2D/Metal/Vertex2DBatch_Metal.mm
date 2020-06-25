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

# include "Vertex2DBatch_Metal.hpp"

namespace s3d
{
	void Vertex2DBatch_Metal::init(id<MTLDevice> device)
	{
		for(size_t i = 0; i < MaxInflightBuffers; ++i)
		{
			m_vertexBuffers[i] = [device newBufferWithLength:(sizeof(Vertex2D) * MaxVertices)
													 options:MTLResourceStorageModeShared];
		}
	}

	size_t Vertex2DBatch_Metal::update()
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

	id<MTLBuffer> Vertex2DBatch_Metal::getCurrentBuffer() const
	{
		return m_vertexBuffers[m_currentVertexBufferIndex];
	}

	dispatch_semaphore_t Vertex2DBatch_Metal::getSemaphore() const
	{
		return m_frameBoundarySemaphore;
	}

	Vertex2D* Vertex2DBatch_Metal::request(size_t size)
	{
		if ((m_vertices.size() + size) > MaxVertices)
		{
			return nullptr;
		}
		
		m_vertices.resize(m_vertices.size() + size);
		
		return m_vertices.data() + (m_vertices.size() - size);
	}
}
