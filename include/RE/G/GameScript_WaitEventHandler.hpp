#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/G/GameScript_Internal_BroadcastEventManager.hpp"

namespace RE
{
	class TESWaitStartEvent;
	class TESWaitStopEvent;
}

namespace RE::BSScript
{
	class IVirtualMachine;
}

namespace RE::GameScript
{
	class __declspec(novtable) WaitEventHandler
		: public BSTEventSink<TESWaitStartEvent>,  // 00
		  public BSTEventSink<TESWaitStopEvent>,   // 08
		  public BSTSingletonSDM<WaitEventHandler> // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__WaitEventHandler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__WaitEventHandler };

		~WaitEventHandler() override; // 00

		// override (BSTEventSink<TESWaitStartEvent>)
		BSEventNotifyControl ProcessEvent(const TESWaitStartEvent& a_event, BSTEventSource<TESWaitStartEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESWaitStopEvent>)
		BSEventNotifyControl ProcessEvent(const TESWaitStopEvent& a_event, BSTEventSource<TESWaitStopEvent>* a_eventSource) override; // 01

		[[nodiscard]] static WaitEventHandler* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<WaitEventHandler**>{ ID::GameScript::WaitEventHandler::Singleton };
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm; // 18
		Internal::BroadcastEventManager eventManager;  // 20
	};
	static_assert(sizeof(WaitEventHandler) == 0x40);
}
