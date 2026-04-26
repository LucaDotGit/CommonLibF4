#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/P/PipboyDataGroup.hpp"

namespace RE::RadioManager
{
	class PipboyFrequencyDetectionEvent;
	class PipboyRadioTuningEvent;
}

namespace RE
{
	class __declspec(novtable) PipboyRadioData
		: public PipboyDataGroup,											// 00
		  public BSTEventSink<RadioManager::PipboyFrequencyDetectionEvent>, // 98
		  public BSTEventSink<RadioManager::PipboyRadioTuningEvent>			// A0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyRadioData };
		inline static constexpr auto VTABLE{ VTABLE::PipboyRadioData };

		~PipboyRadioData() override; // 00

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 02
		void DoClearData() override;		  // 03
		void DoClearSink() override;		  // 04

		// override (BSTEventSink<RadioManager::PipboyFrequencyDetectionEvent>)
		BSEventNotifyControl ProcessEvent(const RadioManager::PipboyFrequencyDetectionEvent& a_event, BSTEventSource<RadioManager::PipboyFrequencyDetectionEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<RadioManager::PipboyRadioTuningEvent>)
		BSEventNotifyControl ProcessEvent(const RadioManager::PipboyRadioTuningEvent& a_event, BSTEventSource<RadioManager::PipboyRadioTuningEvent>* a_eventSource) override; // 01

		// members
		PipboyArray* radioStations; // A8
	};
	static_assert(sizeof(PipboyRadioData) == 0xB0);
}
