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

	class __declspec(novtable) HUDRolloverModel
		: public BSTEventSink<TESCommandModeEnterEvent>, // 000
		  public BSTEventSink<TESCommandModeExitEvent>,	 // 008
		  public BSInputEventUser,						 // 010
		  public nsUIDebug::UIDebugLogger_NoOp			 // 020
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDRolloverModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDRolloverModel };

		~HUDRolloverModel() override; // 00

		// override (BSTEventSink<TESCommandModeEnterEvent>)
		BSEventNotifyControl ProcessEvent(const TESCommandModeEnterEvent& a_event, BSTEventSource<TESCommandModeEnterEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESCommandModeExitEvent>)
		BSEventNotifyControl ProcessEvent(const TESCommandModeExitEvent& a_event, BSTEventSource<TESCommandModeExitEvent>* a_eventSource) override; // 01

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent* a_event) override; // 01
		void OnButtonEvent(const ButtonEvent* a_event) override;	// 08

		// members
		HUDQuickContainerDataModel quickContainerModel;									// 020
		BSTValueEventSink<PickRefStateChangedEvent> activatePromptUpdateQueued;			// 2A8
		BSTValueEventSink<QuickContainerStateEvent> quickContainerState;				// 2C0
		BSTValueEventSink<HUDReinitializedEvent> initHUDValuesQueued;					// 398
		BSTValueEventSink<ViewCasterUpdateEvent> viewCasterUpdate;						// 3B0
		BSTValueEventSink<AutoLoadDoorRolloverEvent> autoLoadDoorRollover;				// 408
		BSTValueEventSink<PlayerCommandTypeEvent> playerCurrentCommandType;				// 438
		BSTValueEventSink<MultiActivateUseRolloverEvent> multiActivateUseRollover;		// 458
		BSTValueEventSink<CompanionMenuEnabled> companionMenuEnabledEvent;				// 478
		BSTValueEventSink<InventoryUpdateEvent> inventoryUpdate;						// 490
		BSTValueEventSink<QuickContainerStateRequiresUpdate> quickContainerNeedsUpdate; // 4B0
		BSTValueEventSink<RolloverSuppressedEvent> rolloverSuppressed;					// 4C8
		BSTValueEventSink<IsPipboyActiveEvent> isPipboyActive;							// 4E0
		BSTValueEventSource<HUDCommandModeEvent> inHUDCommandMode;						// 4F8
		BSTValueEventSource<HUDRolloverStateEvent> currentRolloverState;				// 510
		BSTValueEventSource<PlayerCrosshairModeEvent> currentCrosshairMode;				// 550
		BSTValueEventSource<HUDRolloverIsCrime> rolloverIsCrime;						// 568
		BSTValueEventSource<PlayerActivatePickRefEvent> activatePickRef;				// 580
		BSTOptional<BSFixedString> buttonPressRegistered;								// 598
	};
	static_assert(sizeof(HUDRolloverModel) == 0x5A8);
}
