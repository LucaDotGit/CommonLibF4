#pragma once

namespace RE::InventoryInterface
{
	class CountChangedEvent
	{
	public:
		// members
		std::uint32_t inventoryOwnerID; // 0x00
		std::uint32_t itemID;			// 0x04
		std::int32_t newCount;			// 0x08
		std::int32_t oldCount;			// 0x0C
	};

	static_assert(sizeof(CountChangedEvent) == 0x10);
}
