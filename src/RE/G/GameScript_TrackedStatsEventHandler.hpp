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
	class __declspec(novtable) TrackedStatsEventHandler :
		public BSTEventSink<TESTrackedStatsEvent>,		 // 0x00
		public BSTSingletonSDM<TrackedStatsEventHandler> // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__TrackedStatsEventHandler;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__TrackedStatsEventHandler;

		~TrackedStatsEventHandler() override; // 0x00

		// override (BSTEventSink<TESTrackedStatsEvent>)
		auto ProcessEvent(
			const TESTrackedStatsEvent& a_event,
			BSTEventSource<TESTrackedStatsEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> TrackedStatsEventHandler*
		{
			static const auto SINGLETON =
				REL::Relocation<TrackedStatsEventHandler**>{ID::GameScript::TrackedStatsEventHandler::Singleton};
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm;											// 0x10
		mutable BSSpinLock trackedStatsLock;													// 0x18
		BSTHashMap<BSFixedString, BSTSmartPointer<Internal::StatsEventList>> registeredObjects; // 0x20
	};

	static_assert(sizeof(TrackedStatsEventHandler) == 0x50);
}
