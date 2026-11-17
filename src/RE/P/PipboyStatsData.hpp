#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/P/PipboyDataGroup.hpp"

namespace RE
{
	class ConditionBoyEvent;
}

namespace RE::ActorItemEquipped
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

namespace RE::PlayerActiveEffectChanged
{
	class Event;
}

namespace RE
{
	class __declspec(novtable) PipboyStatsData :
		public PipboyDataGroup,										   // 0x00
		public BSTEventSink<ActorValueEvents::ActorValueChangedEvent>, // 0x98
		public BSTEventSink<BGSInventoryListEvent::Event>,			   // 0xA0
		public BSTEventSink<PlayerActiveEffectChanged::Event>,		   // 0xA8
		public BSTEventSink<ConditionBoyEvent>,						   // 0xB0
		public BSTEventSink<ActorItemEquipped::Event>,				   // 0xB8
		public BSTEventSink<BGSInventoryItemEvent::Event>			   // 0xC0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyStatsData;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyStatsData;

		~PipboyStatsData() override; // 0x00

		auto ProcessEvent(
			const ActorValueEvents::ActorValueChangedEvent& a_event,
			BSTEventSource<ActorValueEvents::ActorValueChangedEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01
		auto ProcessEvent(
			const BGSInventoryListEvent::Event& a_event,
			BSTEventSource<BGSInventoryListEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01
		auto ProcessEvent(
			const PlayerActiveEffectChanged::Event& a_event,
			BSTEventSource<PlayerActiveEffectChanged::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01
		auto ProcessEvent(
			const ConditionBoyEvent& a_event,
			BSTEventSource<ConditionBoyEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01
		auto ProcessEvent(
			const ActorItemEquipped::Event& a_event,
			BSTEventSource<ActorItemEquipped::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01
		auto ProcessEvent(
			const BGSInventoryItemEvent::Event& a_event,
			BSTEventSource<BGSInventoryItemEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 0x07
		void DoClearData() override;		  // 0x08
		void DoClearSink() override;		  // 0x09

		// members
		PipboyObject* playerStatsObject;												 // 0xC8
		PipboyArray* activeEffectsArray;												 // 0xD0
		BSTHashMap<MagicItem*, PipboyObject*> activeEffectsMap;							 // 0xD8
		BSTHashMap<BSTSmartPointer<ActiveEffect>, PipboyObject*> activeEffectEntriesMap; // 0x108
	};

	static_assert(sizeof(PipboyStatsData) == 0x138);
}
