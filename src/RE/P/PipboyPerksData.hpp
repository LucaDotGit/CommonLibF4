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
	class __declspec(novtable) PipboyPerksData :
		public PipboyDataGroup,										// 0x00
		public BSTEventSink<PerkValueEvents::PerkValueChangedEvent> // 0x98
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyPerksData;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyPerksData;

		~PipboyPerksData() override; // 0x00

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 0x02
		void DoClearData() override;		  // 0x03
		void DoClearSink() override;		  // 0x04

		// override (BSTEventSink<PerkValueEvents::PerkValueChangedEvent>)
		auto ProcessEvent(
			const PerkValueEvents::PerkValueChangedEvent& a_event,
			BSTEventSource<PerkValueEvents::PerkValueChangedEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		PipboyArray* perkChains;				 // 0xA0
		BSTArray<const BGSPerk*> perkChainRoots; // 0xA8
		BSTArray<PipboyObject*> perksArray;		 // 0xC0
	};

	static_assert(sizeof(PipboyPerksData) == 0xD8);
}
