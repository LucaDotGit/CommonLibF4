#pragma once

namespace RE::BSGraphics
{
	class VertexBuffer;

	class DynamicTriShapeData
	{
	public:
		// members
		VertexBuffer* vb;		  // 00
		std::uint32_t dataStride; // 08
	};
	static_assert(sizeof(DynamicTriShapeData) == 0x10);
}
