#pragma once

namespace RE::BSScript
{
	class MemoryPage
	{
	public:
		// members
		std::uint32_t pageSize; // 00
	};
	static_assert(sizeof(MemoryPage) == 0x04);
}
