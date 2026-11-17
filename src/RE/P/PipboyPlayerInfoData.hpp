#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/P/PipboyDataGroup.hpp"

namespace RE
{
	class PerkPointIncreaseEvent;
	class PlayerUpdateEvent;
}

namespace RE::ActorEquipManagerEvent
{
	class Event;
}

namespace RE::ActorValueEvents
{
	class ActorValueChangedEvent;
}

namespace RE::BGSInventoryItemEvent
{
	class Event;
}

namespace RE::BGSInventoryListEvent
{
	class Event;
}

namespace RE::HourPassed
{
	class Event;
}

namespace RE::LevelIncrease
{
	class Event;
}

namespace RE::PerkValueEvents
{
	class PerkEntryUpdatedEvent;
}

namespace RE::PlayerActiveEffectChanged
{
	class Event;
}

namespace RE::PlayerCharacterQuestEvent
{
	class Event;
}

namespace RE::PlayerDifficultySettingChanged
{
	class Event;
}

namespace RE::SPECIALMenuEvent
{
	class NameChangedEvent;
}

namespace RE
{
	class __declspec(novtable) PipboyPlayerInfoData :
		public PipboyDataGroup,										   // 0x00
		public BSTEventSink<ActorValueEvents::ActorValueChangedEvent>, // 0x98
		public BSTEventSink<BGSInventoryListEvent::Event>,			   // 0xA0
		public BSTEventSink<ActorEquipManagerEvent::Event>,			   // 0xA8
		public BSTEventSink<LevelIncrease::Event>,					   // 0xB0
		public BSTEventSink<PerkPointIncreaseEvent>,				   // 0xB8
		public BSTEventSink<PerkValueEvents::PerkEntryUpdatedEvent>,   // 0xC0
		public BSTEventSink<HourPassed::Event>,						   // 0xC8
		public BSTEventSink<SPECIALMenuEvent::NameChangedEvent>,	   // 0xD0
		public BSTEventSink<PlayerUpdateEvent>,						   // 0xD8
		public BSTEventSink<BGSInventoryItemEvent::Event>,			   // 0xE0
		public BSTEventSink<PlayerActiveEffectChanged::Event>,		   // 0xE8
		public BSTEventSink<PlayerCharacterQuestEvent::Event>,		   // 0xF0
		public BSTEventSink<PlayerDifficultySettingChanged::Event>	   // 0xF8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyPlayerInfoData;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyPlayerInfoData;

		~PipboyPlayerInfoData() override; // 0x00

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 0x02
		void DoClearData() override;		  // 0x03
		void DoClearSink() override;		  // 0x04

		// override (BSTEventSink<ActorValueEvents::ActorValueChangedEvent>)
		auto ProcessEvent(
			const ActorValueEvents::ActorValueChangedEvent& a_event,
			BSTEventSource<ActorValueEvents::ActorValueChangedEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSInventoryListEvent::Event>)
		auto ProcessEvent(
			const BGSInventoryListEvent::Event& a_event,
			BSTEventSource<BGSInventoryListEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<ActorEquipManagerEvent::Event>)
		auto ProcessEvent(
			const ActorEquipManagerEvent::Event& a_event,
			BSTEventSource<ActorEquipManagerEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<LevelIncrease::Event>)
		auto ProcessEvent(
			const LevelIncrease::Event& a_event,
			BSTEventSource<LevelIncrease::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PerkPointIncreaseEvent>)
		auto ProcessEvent(
			const PerkPointIncreaseEvent& a_event,
			BSTEventSource<PerkPointIncreaseEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PerkValueEvents::PerkEntryUpdatedEvent>)
		auto ProcessEvent(
			const PerkValueEvents::PerkEntryUpdatedEvent& a_event,
			BSTEventSource<PerkValueEvents::PerkEntryUpdatedEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<HourPassed::Event>)
		auto ProcessEvent(
			const HourPassed::Event& a_event,
			BSTEventSource<HourPassed::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<SPECIALMenuEvent::NameChangedEvent>)
		auto ProcessEvent(
			const SPECIALMenuEvent::NameChangedEvent& a_event,
			BSTEventSource<SPECIALMenuEvent::NameChangedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PlayerUpdateEvent>)
		auto ProcessEvent(
			const PlayerUpdateEvent& a_event,
			BSTEventSource<PlayerUpdateEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		/// override (BSTEventSink<BGSInventoryItemEvent::Event>)
		auto ProcessEvent(
			const BGSInventoryItemEvent::Event& a_event,
			BSTEventSource<BGSInventoryItemEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PlayerActiveEffectChanged::Event>)
		auto ProcessEvent(
			const PlayerActiveEffectChanged::Event& a_event,
			BSTEventSource<PlayerActiveEffectChanged::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PlayerCharacterQuestEvent::Event>)
		auto ProcessEvent(
			const PlayerCharacterQuestEvent::Event& a_event,
			BSTEventSource<PlayerCharacterQuestEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PlayerDifficultySettingChanged::Event>)
		auto ProcessEvent(
			const PlayerDifficultySettingChanged::Event& a_event,
			BSTEventSource<PlayerDifficultySettingChanged::Event>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		void UpdateArmorData()
		{
			using FuncType = decltype(&PipboyPlayerInfoData::UpdateCarryWeightData);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyPlayerInfoData::UpdateArmorData);
			std::invoke(FUNC, this);
		}

		void UpdateCarryWeightData()
		{
			using FuncType = decltype(&PipboyPlayerInfoData::UpdateCarryWeightData);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyPlayerInfoData::UpdateCarryWeightData);
			std::invoke(FUNC, this);
		}

		void UpdateGoldData()
		{
			using FuncType = decltype(&PipboyPlayerInfoData::UpdateCarryWeightData);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyPlayerInfoData::UpdateGoldData);
			std::invoke(FUNC, this);
		}

		void UpdateWeaponData()
		{
			using FuncType = decltype(&PipboyPlayerInfoData::UpdateCarryWeightData);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyPlayerInfoData::UpdateWeaponData);
			std::invoke(FUNC, this);
		}

		// members
		PipboyObject* playerInfoObject;
	};

	static_assert(sizeof(PipboyPlayerInfoData) == 0x108);
}
