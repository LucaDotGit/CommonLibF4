#pragma once

namespace RE
{
	class BGSInventoryItem;
}

namespace RE::InventoryInterface
{
	class FavoriteChangedEvent
	{
	public:
		// members
		BGSInventoryItem* itemAffected; // 0x00
	};

	static_assert(sizeof(FavoriteChangedEvent) == 0x08);
}
