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

	class BGSInventoryInterface :
		public BSTSingletonSDM<BGSInventoryInterface>,					// 0x00
		public BSTEventSource<InventoryInterface::CountChangedEvent>,	// 0x08
		public BSTEventSource<InventoryInterface::FavoriteChangedEvent> // 0x60
	{
	public:
		class Agent
		{
		public:
			// members
			std::uint32_t handleID;	   // 0x00
			ObjectRefHandle itemOwner; // 0x04
			std::uint16_t listIndex;   // 0x08
			std::uint16_t refCount;	   // 0x0A
		};

		static_assert(sizeof(Agent) == 0x0C);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BGSInventoryInterface*
		{
			static const auto SINGLETON =
				REL::Relocation<BGSInventoryInterface**>{ID::BGSInventoryInterface::Singleton};
			return *SINGLETON;
		}

		[[nodiscard]]
		auto RequestInventoryItem(const std::uint32_t& a_handleID) const -> const BGSInventoryItem*
		{
			using FuncType = decltype(&BGSInventoryInterface::RequestInventoryItem);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryInterface::RequestInventoryItem);
			return std::invoke(FUNC, this, a_handleID);
		}

		[[nodiscard]]
		auto ForceMergeStacks(const std::uint32_t& a_handleID) -> bool
		{
			using FuncType = decltype(&BGSInventoryInterface::ForceMergeStacks);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryInterface::ForceMergeStacks);
			return std::invoke(FUNC, this, a_handleID);
		}

		// members
		BSTArray<Agent> agentArray; // 0xB8
	};

	static_assert(sizeof(BGSInventoryInterface) == 0xD0);
}
