#pragma once

#include "RE/B/BSGraphics_VertexDesc.hpp"

namespace RE::BSGraphics
{
	class IndexBuffer;
	class VertexBuffer;

	class TriShape
	{
	public:
		VertexDesc vertexDesc;		// 00
		VertexBuffer* vertexBuffer; // 08
		IndexBuffer* indexBuffer;	// 10
		std::uint32_t refCount;		// 18
	};
	static_assert(sizeof(TriShape) == 0x20);
}
