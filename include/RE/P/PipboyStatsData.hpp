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
	class __declspec(novtable) PipboyStatsData
		: public PipboyDataGroup,										 // 00
		  public BSTEventSink<ActorValueEvents::ActorValueChangedEvent>, // 98
		  public BSTEventSink<BGSInventoryListEvent::Event>,			 // A0
		  public BSTEventSink<PlayerActiveEffectChanged::Event>,		 // A8
		  public BSTEventSink<ConditionBoyEvent>,						 // B0
		  public BSTEventSink<ActorItemEquipped::Event>,				 // B8
		  public BSTEventSink<BGSInventoryItemEvent::Event>				 // C0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyStatsData };
		inline static constexpr auto VTABLE{ VTABLE::PipboyStatsData };

		~PipboyStatsData() override; // 00

		BSEventNotifyControl ProcessEvent(const ActorValueEvents::ActorValueChangedEvent& a_event, BSTEventSource<ActorValueEvents::ActorValueChangedEvent>* a_eventSource) override; // 01
		BSEventNotifyControl ProcessEvent(const BGSInventoryListEvent::Event& a_event, BSTEventSource<BGSInventoryListEvent::Event>* a_eventSource) override;						  // 01
		BSEventNotifyControl ProcessEvent(const PlayerActiveEffectChanged::Event& a_event, BSTEventSource<PlayerActiveEffectChanged::Event>* a_eventSource) override;				  // 01
		BSEventNotifyControl ProcessEvent(const ConditionBoyEvent& a_event, BSTEventSource<ConditionBoyEvent>* a_eventSource) override;												  // 01
		BSEventNotifyControl ProcessEvent(const ActorItemEquipped::Event& a_event, BSTEventSource<ActorItemEquipped::Event>* a_eventSource) override;								  // 01
		BSEventNotifyControl ProcessEvent(const BGSInventoryItemEvent::Event& a_event, BSTEventSource<BGSInventoryItemEvent::Event>* a_eventSource) override;						  // 01

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 07
		void DoClearData() override;		  // 08
		void DoClearSink() override;		  // 09

		// members
		PipboyObject* playerStatsObject;												 // C8
		PipboyArray* activeEffectsArray;												 // D0
		BSTHashMap<MagicItem*, PipboyObject*> activeEffectsMap;							 // D8
		BSTHashMap<BSTSmartPointer<ActiveEffect>, PipboyObject*> activeEffectEntriesMap; // 108
	};
	static_assert(sizeof(PipboyStatsData) == 0x138);
}
