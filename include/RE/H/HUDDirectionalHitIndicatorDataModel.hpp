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

	class __declspec(novtable) HUDDirectionalHitIndicatorDataModel
		: public BSTEventSink<HUDModeEvent>, // 00
		  public BSTEventSink<TESHitEvent>	 // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDDirectionalHitIndicatorDataModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDDirectionalHitIndicatorDataModel };

		~HUDDirectionalHitIndicatorDataModel() override; // 00

		// override (BSTEventSink<HUDModeEvent>)
		BSEventNotifyControl ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESHitEvent>)
		BSEventNotifyControl ProcessEvent(const TESHitEvent& a_event, BSTEventSource<TESHitEvent>* a_eventSource) override; // 01

		// members
		BSTValueEventSource<DirectionalHitIndicatorResultEvent> currentDirectionalHitIndicators; // 10
		BSTArray<BSTPair<std::uint64_t, ActorHandle>> queuedHitSources;							 // 40
		HUDModes validHUDModes;																	 // 58
	};
	static_assert(sizeof(HUDDirectionalHitIndicatorDataModel) == 0x78);
}
