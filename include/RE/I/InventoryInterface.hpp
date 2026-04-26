#pragma once

#include "RE/B/BSCRC32.hpp"

namespace RE
{
	class BGSInventoryItem;
}

namespace RE::InventoryInterface
{
	class CountChangedEvent
	{
	public:
		// members
		std::uint32_t inventoryOwnerID; // 00
		std::uint32_t itemID;			// 04
		std::int32_t newCount;			// 08
		std::int32_t oldCount;			// 0C
	};
	static_assert(sizeof(CountChangedEvent) == 0x10);

	class FavoriteChangedEvent
	{
	public:
		// members
		BGSInventoryItem* itemAffected; // 00
	};
	static_assert(sizeof(FavoriteChangedEvent) == 0x08);

	class Handle
	{
	public:
		inline static constexpr auto EMPTY_HANDLE = std::numeric_limits<std::uint32_t>::max();

		// members
		std::uint32_t id; // 00
	};
	static_assert(sizeof(Handle) == 0x04);
}

namespace RE
{
	template <>
	struct BSCRC32<RE::InventoryInterface::Handle>
	{
		[[nodiscard]] constexpr std::uint32_t operator()(RE::InventoryInterface::Handle a_key) const noexcept
		{
			return RE::HashCRC32(a_key.id);
		}
	};
}

namespace std
{
	template <>
	struct hash<RE::InventoryInterface::Handle>
	{
		[[nodiscard]] std::size_t operator()(RE::InventoryInterface::Handle a_key) const noexcept
		{
			return REX::Hash(a_key.id);
		}
	};
}
