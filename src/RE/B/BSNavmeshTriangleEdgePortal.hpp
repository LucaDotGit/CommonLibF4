#pragma once

namespace RE
{
	class BSNavmeshTriangleEdgePortal
	{
	public:
		// members
		std::uint32_t otherMeshID; // 0x00
		std::uint16_t triangle;	   // 0x04
		std::int8_t edgeIndex;	   // 0x06
	};

	static_assert(sizeof(BSNavmeshTriangleEdgePortal) == 0x08);
}
