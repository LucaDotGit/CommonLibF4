#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/I/InventoryInterface_Handle.hpp"

namespace RE::ActorEquipManagerEvent
{
	class Event;
}

namespace RE
{
	class BGSEquipSlot;
	class BGSObjectInstance;
	class EquippedItem;

	class ActorEquipManager :
		public BSTSingletonSDM<ActorEquipManager>,			 // 0x00
		public BSTEventSource<ActorEquipManagerEvent::Event> // 0x08
	{
	public:
		enum class CanEquipResult : std::int32_t
		{
			Success = 0,
			InvalidItem = 1,
			NoModEquip = 2,
			PAWhileNotInPA = 3,
			NonPAWhileInPA = 4,
			EquipStateLocked = 5,
			ItemBroken = 6,
			NoEquipKeyword = 7
		};

		[[nodiscard]]
		static auto GetSingleton() noexcept -> ActorEquipManager*
		{
			static const auto SINGLETON = REL::Relocation<ActorEquipManager**>(ID::ActorEquipManager::Singleton);
			return *SINGLETON;
		}

		[[nodiscard]]
		auto CanEquip(Actor* a_actor, const InventoryInterface::Handle& a_handleID, std::uint32_t a_stackID)
			-> CanEquipResult
		{
			using FuncType = decltype(&ActorEquipManager::CanEquip);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ActorEquipManager::CanEquip);
			return std::invoke(FUNC, this, a_actor, a_handleID, a_stackID);
		}

		auto EquipObject(
			Actor* a_actor,
			const BGSObjectInstance& a_object,
			std::uint32_t a_stackID,
			std::uint32_t a_number,
			const BGSEquipSlot* a_slot,
			bool a_queueEquip,
			bool a_forceEquip,
			bool a_playSounds,
			bool a_applyNow,
			bool a_locked) -> bool
		{
			using FuncType = decltype(&ActorEquipManager::EquipObject);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ActorEquipManager::EquipObject);
			return std::invoke(
				FUNC,
				this,
				a_actor,
				a_object,
				a_stackID,
				a_number,
				a_slot,
				a_queueEquip,
				a_forceEquip,
				a_playSounds,
				a_applyNow,
				a_locked);
		}

		auto UnequipObject(
			Actor* a_actor,
			const BGSObjectInstance* a_object,
			std::uint32_t a_number,
			const BGSEquipSlot* a_slot,
			std::uint32_t a_stackID,
			bool a_queueEquip,
			bool a_forceEquip,
			bool a_playSounds,
			bool a_applyNow,
			const BGSEquipSlot* a_slotBeingReplaced) -> bool
		{
			using FuncType = decltype(&ActorEquipManager::UnequipObject);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ActorEquipManager::UnequipObject);
			return std::invoke(
				FUNC,
				this,
				a_actor,
				a_object,
				a_number,
				a_slot,
				a_stackID,
				a_queueEquip,
				a_forceEquip,
				a_playSounds,
				a_applyNow,
				a_slotBeingReplaced);
		}

		void UnequipItem(Actor* a_actor, const EquippedItem* a_equippedItem, bool a_queueEquip)
		{
			using FuncType = decltype(&ActorEquipManager::UnequipItem);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ActorEquipManager::UnequipItem);
			std::invoke(FUNC, this, a_actor, a_equippedItem, a_queueEquip);
		}
	};

	static_assert(sizeof(ActorEquipManager) == 0x60);
}
