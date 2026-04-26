#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/P/PipboyDataGroup.hpp"

namespace RE::PerkValueEvents
{
	class PerkValueChangedEvent;
}

namespace RE
{
	class __declspec(novtable) PipboyPerksData
		: public PipboyDataGroup,									  // 00
		  public BSTEventSink<PerkValueEvents::PerkValueChangedEvent> // 98
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyPerksData };
		inline static constexpr auto VTABLE{ VTABLE::PipboyPerksData };

		~PipboyPerksData() override; // 00

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 02
		void DoClearData() override;		  // 03
		void DoClearSink() override;		  // 04

		// override (BSTEventSink<PerkValueEvents::PerkValueChangedEvent>)
		BSEventNotifyControl ProcessEvent(const PerkValueEvents::PerkValueChangedEvent& a_event, BSTEventSource<PerkValueEvents::PerkValueChangedEvent>* a_eventSource) override; // 01

		PipboyArray* perkChains;				 // A0
		BSTArray<const BGSPerk*> perkChainRoots; // A8
		BSTArray<PipboyObject*> perksArray;		 // C0
	};
	static_assert(sizeof(PipboyPerksData) == 0xD8);
}
