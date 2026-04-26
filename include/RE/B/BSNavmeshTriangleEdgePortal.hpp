#pragma once

namespace RE
{
	class BSNavmeshTriangleEdgePortal
	{
	public:
		// members
		std::uint32_t otherMeshID; // 00
		std::uint16_t triangle;	   // 04
		std::int8_t edgeIndex;	   // 06
	};
	static_assert(sizeof(BSNavmeshTriangleEdgePortal) == 0x08);
}
