#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/P/PipboyDataGroup.hpp"

namespace RE::ActorValueEvents
{
	class ActorValueChangedEvent;
}

namespace RE::Workshop
{
	class WorkshopModeEvent;
}

namespace RE
{
	class __declspec(novtable) PipboyWorkshopData
		: public PipboyDataGroup,										 // 00
		  public BSTEventSink<ActorValueEvents::ActorValueChangedEvent>, // 98
		  public BSTEventSink<Workshop::WorkshopModeEvent>				 // A0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyWorkshopData };
		inline static constexpr auto VTABLE{ VTABLE::PipboyStatusData };

		~PipboyWorkshopData() override;

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 02
		void DoClearData() override;		  // 03
		void DoClearSink() override;		  // 04

		// override (BSTEventSink<ActorValueEvents::ActorValueChangedEvent>)
		BSEventNotifyControl ProcessEvent(const ActorValueEvents::ActorValueChangedEvent& a_event, BSTEventSource<ActorValueEvents::ActorValueChangedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<Workshop::WorkshopModeEvent>)
		BSEventNotifyControl ProcessEvent(const Workshop::WorkshopModeEvent& a_event, BSTEventSource<Workshop::WorkshopModeEvent>* a_eventSource) override; // 01

		// members
		PipboyArray* workshopArray;										 // A8
		BSTHashMap<std::uint32_t, PipboyObject*> workshopMap;			 // B0
		BSTHashMap<BSFixedStringCS, std::int32_t> ratingUpdateFunctions; // E0
		BSTHashMap<BSFixedStringCS, std::uint32_t> getValueFunctions;	 // 110
	};
	static_assert(sizeof(PipboyWorkshopData) == 0x140);
}
