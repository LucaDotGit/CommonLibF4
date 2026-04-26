#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/P/PipboyDataGroup.hpp"

namespace RE::ActorValueEvents
{
	class ActorValueChangedEvent;
}

namespace RE
{
	class __declspec(novtable) PipboySpecialData
		: public PipboyDataGroup,										// 00
		  public BSTEventSink<ActorValueEvents::ActorValueChangedEvent> // 98
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboySpecialData };
		inline static constexpr auto VTABLE{ VTABLE::PipboySpecialData };

		~PipboySpecialData() override;

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 01
		void DoClearData() override;		  // 02
		void DoClearSink() override;		  // 03

		// add
		BSEventNotifyControl ProcessEvent(const ActorValueEvents::ActorValueChangedEvent& a_event, BSTEventSource<ActorValueEvents::ActorValueChangedEvent>* a_eventSource) override; // 01

		// members
		PipboyArray* specialsArray; // A0
	};
	static_assert(sizeof(PipboySpecialData) == 0xA8);
}
