#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class TESTrackedStatsEvent;
}

namespace RE::BSScript
{
	class IVirtualMachine;
}

namespace RE::GameScript::Internal
{
	class StatsEventList;
}

namespace RE::GameScript
{
	class __declspec(novtable) TrackedStatsEventHandler
		: public BSTEventSink<TESTrackedStatsEvent>,	   // 00
		  public BSTSingletonSDM<TrackedStatsEventHandler> // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__TrackedStatsEventHandler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__TrackedStatsEventHandler };

		~TrackedStatsEventHandler() override; // 00

		// override (BSTEventSink<TESTrackedStatsEvent>)
		BSEventNotifyControl ProcessEvent(const TESTrackedStatsEvent& a_event, BSTEventSource<TESTrackedStatsEvent>* a_eventSource) override; // 01

		[[nodiscard]] static TrackedStatsEventHandler* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<TrackedStatsEventHandler**>{ ID::GameScript::TrackedStatsEventHandler::Singleton };
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm;											// 10
		mutable BSSpinLock trackedStatsLock;													// 18
		BSTHashMap<BSFixedString, BSTSmartPointer<Internal::StatsEventList>> registeredObjects; // 20
	};
	static_assert(sizeof(TrackedStatsEventHandler) == 0x50);
}
