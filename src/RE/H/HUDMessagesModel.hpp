#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTObjectArena.hpp"
#include "RE/C/CanDisplayNextHUDMessage.hpp"
#include "RE/H/HUDMessageDisplayDataEvent.hpp"
#include "RE/H/HUDModes.hpp"
#include "RE/H/HUDQuestVaultBoySwfName.hpp"
#include "RE/H/HasHUDMessagesEvent.hpp"
#include "RE/S/ShowingFeaturedItemVaultBoyEvent.hpp"

namespace RE
{
	class ClearHUDMessagesEvent;
	class HUDInventoryChangeMessageEvent;
	class HUDModeEvent;
	class ShowHUDMessageEvent;
	class ThrottleMessageData;

	class __declspec(novtable) HUDMessagesModel :
		public BSTEventSink<HUDInventoryChangeMessageEvent>, // 0x000
		public BSTEventSink<ShowHUDMessageEvent>,			 // 0x008
		public BSTEventSink<ClearHUDMessagesEvent>,			 // 0x010
		public BSTEventSink<HUDModeEvent>					 // 0x018
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HUDMessagesModel;
		inline static constexpr const auto& VTABLE = VTABLE::HUDMessagesModel;

		~HUDMessagesModel() override; // 0x00

		// override (BSTEventSink<HUDInventoryChangeMessageEvent>)
		auto ProcessEvent(
			const HUDInventoryChangeMessageEvent& a_event,
			BSTEventSource<HUDInventoryChangeMessageEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<ShowHUDMessageEvent>)
		auto ProcessEvent(
			const ShowHUDMessageEvent& a_event,
			BSTEventSource<ShowHUDMessageEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<ClearHUDMessagesEvent>)
		auto ProcessEvent(
			const ClearHUDMessagesEvent& a_event,
			BSTEventSource<ClearHUDMessagesEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<HUDModeEvent>)
		auto ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// members
		BSTValueEventSource<HUDMessageDisplayDataEvent> nextMessageData;				 // 0x020
		BSTValueEventSink<CanDisplayNextHUDMessage> canShowNextMessage;					 // 0x050
		BSTValueEventSink<HUDQuestVaultBoySwfName> questVaultBoySwfName;				 // 0x069
		BSTValueEventSink<HasHUDMessagesEvent> hasHUDMessages;							 // 0x090
		BSTValueEventSink<ShowingFeaturedItemVaultBoyEvent> showingFeaturedItemVaultBoy; // 0x0A8
		BSTHeapObjectArena<ThrottleMessageData, 0x08> throttles;						 // 0x0C0
		mutable BSSpinLock throttleArenaLock;											 // 0x0F8
		BSTHeapObjectArena<ShowHUDMessageEvent, 0x08> queuedMessages;					 // 0x100
		mutable BSSpinLock queuedMessagesLock;											 // 0x138
		HUDModes messagesHUDModes;														 // 0x140
	};

	static_assert(sizeof(HUDMessagesModel) == 0x160);
}
