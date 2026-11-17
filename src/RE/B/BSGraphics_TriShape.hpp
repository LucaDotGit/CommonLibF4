#pragma once

#include "RE/B/BSGraphics_VertexDesc.hpp"

namespace RE::BSGraphics
{
	class IndexBuffer;
	class VertexBuffer;

	class TriShape
	{
	public:
		VertexDesc vertexDesc;		// 0x00
		VertexBuffer* vertexBuffer; // 0x08
		IndexBuffer* indexBuffer;	// 0x10
		std::uint32_t refCount;		// 0x18
	};

	static_assert(sizeof(TriShape) == 0x20);
}
