#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE::InventoryInterface
{
	class CountChangedEvent;
	class FavoriteChangedEvent;
}

namespace RE
{
	class BGSInventoryItem;

	class BGSInventoryInterface
		: public BSTSingletonSDM<BGSInventoryInterface>,				  // 00
		  public BSTEventSource<InventoryInterface::CountChangedEvent>,	  // 08
		  public BSTEventSource<InventoryInterface::FavoriteChangedEvent> // 60
	{
	public:
		class Agent
		{
		public:
			// members
			std::uint32_t handleID;	   // 00
			ObjectRefHandle itemOwner; // 04
			std::uint16_t listIndex;   // 08
			std::uint16_t refCount;	   // 0A
		};
		static_assert(sizeof(Agent) == 0x0C);

		[[nodiscard]] static BGSInventoryInterface* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<BGSInventoryInterface**>{ ID::BGSInventoryInterface::Singleton };
			return *SINGLETON;
		}

		[[nodiscard]] const BGSInventoryItem* RequestInventoryItem(const std::uint32_t& a_handleID) const
		{
			using FuncType = decltype(&BGSInventoryInterface::RequestInventoryItem);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryInterface::RequestInventoryItem };
			return std::invoke(FUNC, this, a_handleID);
		}

		[[nodiscard]] bool ForceMergeStacks(const std::uint32_t& a_handleID)
		{
			using FuncType = decltype(&BGSInventoryInterface::ForceMergeStacks);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryInterface::ForceMergeStacks };
			return std::invoke(FUNC, this, a_handleID);
		}

		// members
		BSTArray<Agent> agentArray; // B8
	};
	static_assert(sizeof(BGSInventoryInterface) == 0xD0);
}
