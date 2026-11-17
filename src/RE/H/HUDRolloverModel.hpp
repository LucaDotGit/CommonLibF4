#pragma once

#include "RE/A/AutoLoadDoorRolloverEvent.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSInputEventUser.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTOptional.hpp"
#include "RE/C/CompanionMenuEnabled.hpp"
#include "RE/H/HUDCommandModeEvent.hpp"
#include "RE/H/HUDQuickContainerDataModel.hpp"
#include "RE/H/HUDReinitializedEvent.hpp"
#include "RE/H/HUDRolloverIsCrime.hpp"
#include "RE/H/HUDRolloverStateEvent.hpp"
#include "RE/I/InventoryUpdateEvent.hpp"
#include "RE/I/IsPipboyActiveEvent.hpp"
#include "RE/M/MultiActivateUseRolloverEvent.hpp"
#include "RE/N/nsUIDebug_UIDebugLogger_NoOp.hpp"
#include "RE/P/PickRefStateChangedEvent.hpp"
#include "RE/P/PlayerActivatePickRefEvent.hpp"
#include "RE/P/PlayerCommandTypeEvent.hpp"
#include "RE/P/PlayerCrosshairModeEvent.hpp"
#include "RE/Q/QuickContainerStateEvent.hpp"
#include "RE/Q/QuickContainerStateRequiresUpdate.hpp"
#include "RE/R/RolloverSuppressedEvent.hpp"
#include "RE/V/ViewCasterUpdateEvent.hpp"

namespace RE
{
	class TESCommandModeEnterEvent;
	class TESCommandModeExitEvent;

	class __declspec(novtable) HUDRolloverModel :
		public BSTEventSink<TESCommandModeEnterEvent>, // 0x000
		public BSTEventSink<TESCommandModeExitEvent>,  // 0x008
		public BSInputEventUser,					   // 0x010
		public nsUIDebug::UIDebugLogger_NoOp		   // 0x020
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HUDRolloverModel;
		inline static constexpr const auto& VTABLE = VTABLE::HUDRolloverModel;

		~HUDRolloverModel() override; // 0x00

		// override (BSTEventSink<TESCommandModeEnterEvent>)
		auto ProcessEvent(
			const TESCommandModeEnterEvent& a_event,
			BSTEventSource<TESCommandModeEnterEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESCommandModeExitEvent>)
		auto ProcessEvent(
			const TESCommandModeExitEvent& a_event,
			BSTEventSource<TESCommandModeExitEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSInputEventUser)
		auto ShouldHandleEvent(const InputEvent* a_event) -> bool override; // 0x01
		void OnButtonEvent(const ButtonEvent* a_event) override;			// 0x08

		// members
		HUDQuickContainerDataModel quickContainerModel;									// 0x020
		BSTValueEventSink<PickRefStateChangedEvent> activatePromptUpdateQueued;			// 0x2A8
		BSTValueEventSink<QuickContainerStateEvent> quickContainerState;				// 0x2C0
		BSTValueEventSink<HUDReinitializedEvent> initHUDValuesQueued;					// 0x398
		BSTValueEventSink<ViewCasterUpdateEvent> viewCasterUpdate;						// 0x3B0
		BSTValueEventSink<AutoLoadDoorRolloverEvent> autoLoadDoorRollover;				// 0x408
		BSTValueEventSink<PlayerCommandTypeEvent> playerCurrentCommandType;				// 0x438
		BSTValueEventSink<MultiActivateUseRolloverEvent> multiActivateUseRollover;		// 0x458
		BSTValueEventSink<CompanionMenuEnabled> companionMenuEnabledEvent;				// 0x478
		BSTValueEventSink<InventoryUpdateEvent> inventoryUpdate;						// 0x490
		BSTValueEventSink<QuickContainerStateRequiresUpdate> quickContainerNeedsUpdate; // 0x4B0
		BSTValueEventSink<RolloverSuppressedEvent> rolloverSuppressed;					// 0x4C8
		BSTValueEventSink<IsPipboyActiveEvent> isPipboyActive;							// 0x4E0
		BSTValueEventSource<HUDCommandModeEvent> inHUDCommandMode;						// 0x4F8
		BSTValueEventSource<HUDRolloverStateEvent> currentRolloverState;				// 0x510
		BSTValueEventSource<PlayerCrosshairModeEvent> currentCrosshairMode;				// 0x550
		BSTValueEventSource<HUDRolloverIsCrime> rolloverIsCrime;						// 0x568
		BSTValueEventSource<PlayerActivatePickRefEvent> activatePickRef;				// 0x580
		BSTOptional<BSFixedString> buttonPressRegistered;								// 0x598
	};

	static_assert(sizeof(HUDRolloverModel) == 0x5A8);
}
