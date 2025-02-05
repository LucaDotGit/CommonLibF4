#pragma once

#include "RE/Bethesda/BSPointerHandle.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTEvent.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"

namespace RE
{
	class BGSInventoryItem;

	namespace InventoryInterface
	{
		struct CountChangedEvent
		{
		public:
			// members
			std::uint32_t inventoryOwnerID; // 00
			std::uint32_t itemID;			// 04
			std::int32_t newCount;			// 08
			std::int32_t oldCount;			// 0C
		};
		static_assert(sizeof(CountChangedEvent) == 0x10);

		struct FavoriteChangedEvent
		{
		public:
			~FavoriteChangedEvent() noexcept {} // intentional

			// members
			BGSInventoryItem* itemAffected; // 00
		};
		static_assert(sizeof(FavoriteChangedEvent) == 0x8);

		struct Handle
		{
		public:
			~Handle() noexcept {} // intentional

			// members
			std::uint32_t id; // 00
		};
		static_assert(sizeof(Handle) == 0x4);
	}

	class BGSInventoryInterface : BSTSingletonSDM<BGSInventoryInterface>,				   // 00
								  BSTEventSource<InventoryInterface::CountChangedEvent>,   // 08
								  BSTEventSource<InventoryInterface::FavoriteChangedEvent> // 60
	{
	public:
		struct Agent
		{
		public:
			// members
			std::uint32_t handleID;	   // 00
			ObjectRefHandle itemOwner; // 04
			std::uint16_t listIndex;   // 08
			std::uint16_t refCount;	   // 0A
		};
		static_assert(sizeof(Agent) == 0xC);

		[[nodiscard]] static BGSInventoryInterface* GetSingleton()
		{
			static REL::Relocation<BGSInventoryInterface**> singleton{ REL::RelocationID(501899, 2689299) };
			return *singleton;
		}

		[[nodiscard]] const BGSInventoryItem* RequestInventoryItem(const std::uint32_t& a_handleID) const
		{
			using func_t = decltype(&BGSInventoryInterface::RequestInventoryItem);
			static REL::Relocation<func_t> func{ REL::RelocationID(1200959, 2194009) };
			return func(this, a_handleID);
		}

		// members
		BSTArray<Agent> agentArray; // B8
	};
	static_assert(sizeof(BGSInventoryInterface) == 0xD0);
}
