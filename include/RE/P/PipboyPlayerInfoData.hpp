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
	class __declspec(novtable) PipboyPlayerInfoData
		: public PipboyDataGroup,										 // 00
		  public BSTEventSink<ActorValueEvents::ActorValueChangedEvent>, // 98
		  public BSTEventSink<BGSInventoryListEvent::Event>,			 // A0
		  public BSTEventSink<ActorEquipManagerEvent::Event>,			 // A8
		  public BSTEventSink<LevelIncrease::Event>,					 // B0
		  public BSTEventSink<PerkPointIncreaseEvent>,					 // B8
		  public BSTEventSink<PerkValueEvents::PerkEntryUpdatedEvent>,	 // C0
		  public BSTEventSink<HourPassed::Event>,						 // C8
		  public BSTEventSink<SPECIALMenuEvent::NameChangedEvent>,		 // D0
		  public BSTEventSink<PlayerUpdateEvent>,						 // D8
		  public BSTEventSink<BGSInventoryItemEvent::Event>,			 // E0
		  public BSTEventSink<PlayerActiveEffectChanged::Event>,		 // E8
		  public BSTEventSink<PlayerCharacterQuestEvent::Event>,		 // F0
		  public BSTEventSink<PlayerDifficultySettingChanged::Event>	 // F8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyPlayerInfoData };
		inline static constexpr auto VTABLE{ VTABLE::PipboyPlayerInfoData };

		~PipboyPlayerInfoData() override; // 00

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 02
		void DoClearData() override;		  // 03
		void DoClearSink() override;		  // 04

		// override (BSTEventSink<ActorValueEvents::ActorValueChangedEvent>)
		BSEventNotifyControl ProcessEvent(const ActorValueEvents::ActorValueChangedEvent& a_event, BSTEventSource<ActorValueEvents::ActorValueChangedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSInventoryListEvent::Event>)
		BSEventNotifyControl ProcessEvent(const BGSInventoryListEvent::Event& a_event, BSTEventSource<BGSInventoryListEvent::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<ActorEquipManagerEvent::Event>)
		BSEventNotifyControl ProcessEvent(const ActorEquipManagerEvent::Event& a_event, BSTEventSource<ActorEquipManagerEvent::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<LevelIncrease::Event>)
		BSEventNotifyControl ProcessEvent(const LevelIncrease::Event& a_event, BSTEventSource<LevelIncrease::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<PerkPointIncreaseEvent>)
		BSEventNotifyControl ProcessEvent(const PerkPointIncreaseEvent& a_event, BSTEventSource<PerkPointIncreaseEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<PerkValueEvents::PerkEntryUpdatedEvent>)
		BSEventNotifyControl ProcessEvent(const PerkValueEvents::PerkEntryUpdatedEvent& a_event, BSTEventSource<PerkValueEvents::PerkEntryUpdatedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<HourPassed::Event>)
		BSEventNotifyControl ProcessEvent(const HourPassed::Event& a_event, BSTEventSource<HourPassed::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<SPECIALMenuEvent::NameChangedEvent>)
		BSEventNotifyControl ProcessEvent(const SPECIALMenuEvent::NameChangedEvent& a_event, BSTEventSource<SPECIALMenuEvent::NameChangedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<PlayerUpdateEvent>)
		BSEventNotifyControl ProcessEvent(const PlayerUpdateEvent& a_event, BSTEventSource<PlayerUpdateEvent>* a_eventSource) override; // 01

		/// override (BSTEventSink<BGSInventoryItemEvent::Event>)
		BSEventNotifyControl ProcessEvent(const BGSInventoryItemEvent::Event& a_event, BSTEventSource<BGSInventoryItemEvent::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<PlayerActiveEffectChanged::Event>)
		BSEventNotifyControl ProcessEvent(const PlayerActiveEffectChanged::Event& a_event, BSTEventSource<PlayerActiveEffectChanged::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<PlayerCharacterQuestEvent::Event>)
		BSEventNotifyControl ProcessEvent(const PlayerCharacterQuestEvent::Event& a_event, BSTEventSource<PlayerCharacterQuestEvent::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<PlayerDifficultySettingChanged::Event>)
		BSEventNotifyControl ProcessEvent(const PlayerDifficultySettingChanged::Event& a_event, BSTEventSource<PlayerDifficultySettingChanged::Event>* a_eventSource) override; // 01

		void UpdateArmorData()
		{
			using FuncType = decltype(&PipboyPlayerInfoData::UpdateCarryWeightData);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyPlayerInfoData::UpdateArmorData };
			FUNC(this);
		}

		void UpdateCarryWeightData()
		{
			using FuncType = decltype(&PipboyPlayerInfoData::UpdateCarryWeightData);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyPlayerInfoData::UpdateCarryWeightData };
			FUNC(this);
		}

		void UpdateGoldData()
		{
			using FuncType = decltype(&PipboyPlayerInfoData::UpdateCarryWeightData);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyPlayerInfoData::UpdateGoldData };
			FUNC(this);
		}

		void UpdateWeaponData()
		{
			using FuncType = decltype(&PipboyPlayerInfoData::UpdateCarryWeightData);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyPlayerInfoData::UpdateWeaponData };
			FUNC(this);
		}

		// members
		PipboyObject* playerInfoObject;
	};
	static_assert(sizeof(PipboyPlayerInfoData) == 0x108);
}
