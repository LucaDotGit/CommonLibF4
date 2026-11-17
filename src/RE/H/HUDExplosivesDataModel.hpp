#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/E/ExplosiveIndicatorResultEvent.hpp"
#include "RE/H/HUDModes.hpp"

namespace RE
{
	class HUDModeEvent;

	class __declspec(novtable) HUDExplosivesDataModel : public BSTEventSink<HUDModeEvent> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HUDExplosivesDataModel;
		inline static constexpr const auto& VTABLE = VTABLE::HUDExplosivesDataModel;

		~HUDExplosivesDataModel() override; // 0x00

		// override (BSTEventSink<HUDModeEvent>)
		auto ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// members
		BSTValueEventSource<ExplosiveIndicatorResultEvent> CurrentExplosiveIndicators; // 0x08
		HUDModes ValidHUDModes;														   // 0x38
	};

	static_assert(sizeof(HUDExplosivesDataModel) == 0x58);
}
