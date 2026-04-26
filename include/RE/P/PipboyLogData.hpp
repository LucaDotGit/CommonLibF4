#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/P/PipboyDataGroup.hpp"

namespace RE
{
	class TESTrackedStatsEvent;

	class __declspec(novtable) PipboyLogData
		: public PipboyDataGroup,					// 00
		  public BSTEventSink<TESTrackedStatsEvent> // 98
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyLogData };
		inline static constexpr auto VTABLE{ VTABLE::PipboyLogData };

		~PipboyLogData() override; // 00

		// override (BSTEventSink<TESTrackedStatsEvent>)
		BSEventNotifyControl ProcessEvent(const TESTrackedStatsEvent& a_event, BSTEventSource<TESTrackedStatsEvent>* a_eventSource) override; // 01

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 02
		void DoClearData() override;		  // 03
		void DoClearSink() override;		  // 04

		// members
		PipboyArray* statTypeArray;						  // A0
		BSTHashMap<BSFixedString, PipboyObject*> statMap; // A8
	};
	static_assert(sizeof(PipboyLogData) == 0xD8);
}
