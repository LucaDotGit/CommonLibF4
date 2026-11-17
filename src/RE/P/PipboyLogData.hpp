#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/P/PipboyDataGroup.hpp"

namespace RE
{
	class TESTrackedStatsEvent;

	class __declspec(novtable) PipboyLogData :
		public PipboyDataGroup,					  // 0x00
		public BSTEventSink<TESTrackedStatsEvent> // 0x98
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyLogData;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyLogData;

		~PipboyLogData() override; // 0x00

		// override (BSTEventSink<TESTrackedStatsEvent>)
		auto ProcessEvent(
			const TESTrackedStatsEvent& a_event,
			BSTEventSource<TESTrackedStatsEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 0x02
		void DoClearData() override;		  // 0x03
		void DoClearSink() override;		  // 0x04

		// members
		PipboyArray* statTypeArray;						  // 0xA0
		BSTHashMap<BSFixedString, PipboyObject*> statMap; // 0xA8
	};

	static_assert(sizeof(PipboyLogData) == 0xD8);
}
