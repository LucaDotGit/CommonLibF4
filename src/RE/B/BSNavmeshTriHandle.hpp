#pragma once

namespace RE
{
	class BSNavmeshInfo;

	class BSNavmeshTriHandle
	{
	public:
		// members
		BSNavmeshInfo* pNavMeshInfo; // 0x00
		std::uint16_t triangle;		 // 0x08
	};

	static_assert(sizeof(BSNavmeshTriHandle) == 0x10);
}
