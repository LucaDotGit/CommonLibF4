#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/D/DirectionalHitIndicatorResultEvent.hpp"
#include "RE/H/HUDModes.hpp"

namespace RE
{
	class HUDModeEvent;
	class TESHitEvent;

	class __declspec(novtable) HUDDirectionalHitIndicatorDataModel :
		public BSTEventSink<HUDModeEvent>, // 0x00
		public BSTEventSink<TESHitEvent>   // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HUDDirectionalHitIndicatorDataModel;
		inline static constexpr const auto& VTABLE = VTABLE::HUDDirectionalHitIndicatorDataModel;

		~HUDDirectionalHitIndicatorDataModel() override; // 0x00

		// override (BSTEventSink<HUDModeEvent>)
		auto ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESHitEvent>)
		auto ProcessEvent(const TESHitEvent& a_event, BSTEventSource<TESHitEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// members
		BSTValueEventSource<DirectionalHitIndicatorResultEvent> currentDirectionalHitIndicators; // 0x10
		BSTArray<BSTPair<std::uint64_t, ActorHandle>> queuedHitSources;							 // 0x40
		HUDModes validHUDModes;																	 // 0x58
	};

	static_assert(sizeof(HUDDirectionalHitIndicatorDataModel) == 0x78);
}
