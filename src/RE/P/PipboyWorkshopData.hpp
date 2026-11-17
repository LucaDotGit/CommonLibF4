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
	class __declspec(novtable) PipboyWorkshopData :
		public PipboyDataGroup,										   // 0x00
		public BSTEventSink<ActorValueEvents::ActorValueChangedEvent>, // 0x98
		public BSTEventSink<Workshop::WorkshopModeEvent>			   // 0xA0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyWorkshopData;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyStatusData;

		~PipboyWorkshopData() override; // 0x00

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 0x02
		void DoClearData() override;		  // 0x03
		void DoClearSink() override;		  // 0x04

		// override (BSTEventSink<ActorValueEvents::ActorValueChangedEvent>)
		auto ProcessEvent(
			const ActorValueEvents::ActorValueChangedEvent& a_event,
			BSTEventSource<ActorValueEvents::ActorValueChangedEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<Workshop::WorkshopModeEvent>)
		auto ProcessEvent(
			const Workshop::WorkshopModeEvent& a_event,
			BSTEventSource<Workshop::WorkshopModeEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// members
		PipboyArray* workshopArray;										 // 0xA8
		BSTHashMap<std::uint32_t, PipboyObject*> workshopMap;			 // 0xB0
		BSTHashMap<BSFixedStringCS, std::int32_t> ratingUpdateFunctions; // 0xE0
		BSTHashMap<BSFixedStringCS, std::uint32_t> getValueFunctions;	 // 0x110
	};

	static_assert(sizeof(PipboyWorkshopData) == 0x140);
}
