#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/P/PipboyDataGroup.hpp"

namespace RE::ActorValueEvents
{
	class ActorValueChangedEvent;
}

namespace RE
{
	class __declspec(novtable) PipboySpecialData :
		public PipboyDataGroup,										  // 0x00
		public BSTEventSink<ActorValueEvents::ActorValueChangedEvent> // 0x98
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboySpecialData;
		inline static constexpr const auto& VTABLE = VTABLE::PipboySpecialData;

		~PipboySpecialData() override; // 0x00

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 0x01
		void DoClearData() override;		  // 0x02
		void DoClearSink() override;		  // 0x03

		// add
		auto ProcessEvent(
			const ActorValueEvents::ActorValueChangedEvent& a_event,
			BSTEventSource<ActorValueEvents::ActorValueChangedEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// members
		PipboyArray* specialsArray; // 0xA0
	};

	static_assert(sizeof(PipboySpecialData) == 0xA8);
}
