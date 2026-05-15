#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE::ActorEquipManagerEvent
{
	class Event;
}

namespace RE
{
	class BGSEquipSlot;
	class BGSObjectInstance;
	class EquippedItem;

	class ActorEquipManager
		: public BSTSingletonSDM<ActorEquipManager>,		   // 00
		  public BSTEventSource<ActorEquipManagerEvent::Event> // 08
	{
	public:
		enum class CanEquipResult : std::int32_t
		{
			kSuccess = 0,
			kInvalidItem = 1,
			kNoModEquip = 2,
			kPAWhileNotInPA = 3,
			kNonPAWhileInPA = 4,
			kEquipStateLocked = 5,
			kItemBroken = 6,
			kNoEquipKeyword = 7
		};

		[[nodiscard]] static ActorEquipManager* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<ActorEquipManager**>{ ID::ActorEquipManager::Singleton };
			return *SINGLETON;
		}

		bool EquipObject(
			Actor* a_actor,
			const BGSObjectInstance& a_object,
			std::uint32_t a_stackID,
			std::uint32_t a_number,
			const BGSEquipSlot* a_slot,
			bool a_queueEquip,
			bool a_forceEquip,
			bool a_playSounds,
			bool a_applyNow,
			bool a_locked)
		{
			using FuncType = decltype(&ActorEquipManager::EquipObject);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ActorEquipManager::EquipObject };
			return std::invoke(FUNC, this, a_actor, a_object, a_stackID, a_number, a_slot, a_queueEquip, a_forceEquip, a_playSounds, a_applyNow, a_locked);
		}

		bool UnequipObject(
			Actor* a_actor,
			const BGSObjectInstance* a_object,
			std::uint32_t a_number,
			const BGSEquipSlot* a_slot,
			std::uint32_t a_stackID,
			bool a_queueEquip,
			bool a_forceEquip,
			bool a_playSounds,
			bool a_applyNow,
			const BGSEquipSlot* a_slotBeingReplaced)
		{
			using FuncType = decltype(&ActorEquipManager::UnequipObject);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ActorEquipManager::UnequipObject };
			return std::invoke(FUNC, this, a_actor, a_object, a_number, a_slot, a_stackID, a_queueEquip, a_forceEquip, a_playSounds, a_applyNow, a_slotBeingReplaced);
		}

		void UnequipItem(Actor* a_actor, const EquippedItem* a_equippedItem, bool a_queueEquip)
		{
			using FuncType = decltype(&ActorEquipManager::UnequipItem);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::ActorEquipManager::UnequipItem };
			std::invoke(FUNC, this, a_actor, a_equippedItem, a_queueEquip);
		}
	};
	static_assert(sizeof(ActorEquipManager) == 0x60);
}
