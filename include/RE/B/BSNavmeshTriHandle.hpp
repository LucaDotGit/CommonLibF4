#pragma once

namespace RE
{
	class BSNavmeshInfo;

	class BSNavmeshTriHandle
	{
	public:
		// members
		BSNavmeshInfo* pNavMeshInfo; // 00
		std::uint16_t triangle;		 // 08
	};
	static_assert(sizeof(BSNavmeshTriHandle) == 0x10);
}
