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
	class __declspec(novtable) SleepEventHandler :
		public BSTEventSink<TESSleepStartEvent>,  // 0x00
		public BSTEventSink<TESSleepStopEvent>,	  // 0x08
		public BSTSingletonSDM<SleepEventHandler> // 0x10
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__SleepEventHandler;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__SleepEventHandler;

		~SleepEventHandler() override; // 0x00

		// override (BSTEventSink<TESSleepStartEvent>)
		auto ProcessEvent(
			const TESSleepStartEvent& a_event,
			BSTEventSource<TESSleepStartEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESSleepStopEvent>)
		auto ProcessEvent(
			const TESSleepStopEvent& a_event,
			BSTEventSource<TESSleepStopEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> SleepEventHandler*
		{
			static const auto SINGLETON =
				REL::Relocation<SleepEventHandler**>{ID::GameScript::SleepEventHandler::Singleton};
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm; // 0x18
		Internal::BroadcastEventManager eventManager;  // 0x20
	};

	static_assert(sizeof(SleepEventHandler) == 0x40);
}
