#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/E/ExplosiveIndicatorResultEvent.hpp"
#include "RE/H/HUDModes.hpp"

namespace RE
{
	class HUDModeEvent;

	class __declspec(novtable) HUDExplosivesDataModel
		: public BSTEventSink<HUDModeEvent> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDExplosivesDataModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDExplosivesDataModel };

		~HUDExplosivesDataModel() override; // 00

		// override (BSTEventSink<HUDModeEvent>)
		BSEventNotifyControl ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_eventSource) override; // 01

		// members
		BSTValueEventSource<ExplosiveIndicatorResultEvent> CurrentExplosiveIndicators; // 08
		HUDModes ValidHUDModes;														   // 38
	};
	static_assert(sizeof(HUDExplosivesDataModel) == 0x58);
}
