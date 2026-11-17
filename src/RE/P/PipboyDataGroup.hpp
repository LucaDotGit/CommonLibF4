#pragma once

#include "RE/B/BSCriticalSection.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class PipboyArray;
	class PipboyObject;
	class PipboyThrottleManager;
	class PipboyValue;
	class PipboyValueChangedEvent;

	class __declspec(novtable) PipboyDataGroup : public BSTEventSource<PipboyValueChangedEvent> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyDataGroup;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyDataGroup;

		virtual ~PipboyDataGroup() = default; // 0x00

		// add
		virtual auto ProcessEvent(
			const PipboyValueChangedEvent& a_event,
			BSTEventSource<PipboyValueChangedEvent>* a_eventSource) -> BSEventNotifyControl; // 0x01
		virtual void Populate(bool a_unk01) = 0;											 // 0x02
		virtual void DoClearData() = 0;														 // 0x03
		virtual void DoClearSink() = 0;														 // 0x04

		GAME_HEAP_REDEFINE_NEW(PipboyDataGroup);

		// members
		mutable BSCriticalSection pipboyDataMutex; // 0x60
		PipboyThrottleManager* throttleManager;	   // 0x88
		PipboyValue* rootValue;					   // 0x90
	};

	static_assert(sizeof(PipboyDataGroup) == 0x98);
}
