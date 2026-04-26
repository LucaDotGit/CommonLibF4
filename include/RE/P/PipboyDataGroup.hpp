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

	class __declspec(novtable) PipboyDataGroup
		: public BSTEventSource<PipboyValueChangedEvent> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyDataGroup };
		inline static constexpr auto VTABLE{ VTABLE::PipboyDataGroup };

		virtual ~PipboyDataGroup() = default; // 00

		// add
		virtual BSEventNotifyControl ProcessEvent(const PipboyValueChangedEvent& a_event, BSTEventSource<PipboyValueChangedEvent>* a_eventSource); // 01
		virtual void Populate(bool a_unk01) = 0;																								   // 02
		virtual void DoClearData() = 0;																											   // 03
		virtual void DoClearSink() = 0;																											   // 04

		GAME_HEAP_REDEFINE_NEW(PipboyDataGroup);

		// members
		mutable BSCriticalSection pipboyDataMutex; // 60
		PipboyThrottleManager* throttleManager;	   // 88
		PipboyValue* rootValue;					   // 90
	};
	static_assert(sizeof(PipboyDataGroup) == 0x98);
}
