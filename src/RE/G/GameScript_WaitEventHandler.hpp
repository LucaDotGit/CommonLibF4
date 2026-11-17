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
	class __declspec(novtable) WaitEventHandler :
		public BSTEventSink<TESWaitStartEvent>,	 // 0x00
		public BSTEventSink<TESWaitStopEvent>,	 // 0x08
		public BSTSingletonSDM<WaitEventHandler> // 0x10
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__WaitEventHandler;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__WaitEventHandler;

		~WaitEventHandler() override; // 0x00

		// override (BSTEventSink<TESWaitStartEvent>)
		auto ProcessEvent(
			const TESWaitStartEvent& a_event,
			BSTEventSource<TESWaitStartEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESWaitStopEvent>)
		auto ProcessEvent(
			const TESWaitStopEvent& a_event,
			BSTEventSource<TESWaitStopEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> WaitEventHandler*
		{
			static const auto SINGLETON =
				REL::Relocation<WaitEventHandler**>{ID::GameScript::WaitEventHandler::Singleton};
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm; // 0x18
		Internal::BroadcastEventManager eventManager;  // 0x20
	};

	static_assert(sizeof(WaitEventHandler) == 0x40);
}
