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
	class __declspec(novtable) PipboyRadioData :
		public PipboyDataGroup,											  // 0x00
		public BSTEventSink<RadioManager::PipboyFrequencyDetectionEvent>, // 0x98
		public BSTEventSink<RadioManager::PipboyRadioTuningEvent>		  // 0xA0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyRadioData;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyRadioData;

		~PipboyRadioData() override; // 0x00

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 0x02
		void DoClearData() override;		  // 0x03
		void DoClearSink() override;		  // 0x04

		// override (BSTEventSink<RadioManager::PipboyFrequencyDetectionEvent>)
		auto ProcessEvent(
			const RadioManager::PipboyFrequencyDetectionEvent& a_event,
			BSTEventSource<RadioManager::PipboyFrequencyDetectionEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<RadioManager::PipboyRadioTuningEvent>)
		auto ProcessEvent(
			const RadioManager::PipboyRadioTuningEvent& a_event,
			BSTEventSource<RadioManager::PipboyRadioTuningEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// members
		PipboyArray* radioStations; // 0xA8
	};

	static_assert(sizeof(PipboyRadioData) == 0xB0);
}
