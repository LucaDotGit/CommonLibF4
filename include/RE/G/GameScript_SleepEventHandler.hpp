#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/G/GameScript_Internal_BroadcastEventManager.hpp"

namespace RE
{
	class TESSleepStartEvent;
	class TESSleepStopEvent;
}

namespace RE::BSScript
{
	class IVirtualMachine;
}

namespace RE::GameScript
{
	class __declspec(novtable) SleepEventHandler
		: public BSTEventSink<TESSleepStartEvent>,	// 00
		  public BSTEventSink<TESSleepStopEvent>,	// 08
		  public BSTSingletonSDM<SleepEventHandler> // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__SleepEventHandler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__SleepEventHandler };

		~SleepEventHandler() override; // 00

		// override (BSTEventSink<TESSleepStartEvent>)
		BSEventNotifyControl ProcessEvent(const TESSleepStartEvent& a_event, BSTEventSource<TESSleepStartEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESSleepStopEvent>)
		BSEventNotifyControl ProcessEvent(const TESSleepStopEvent& a_event, BSTEventSource<TESSleepStopEvent>* a_eventSource) override; // 01

		[[nodiscard]] static SleepEventHandler* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<SleepEventHandler**>{ ID::GameScript::SleepEventHandler::Singleton };
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm; // 18
		Internal::BroadcastEventManager eventManager;  // 20
	};
	static_assert(sizeof(SleepEventHandler) == 0x40);
}
