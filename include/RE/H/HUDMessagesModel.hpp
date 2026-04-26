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

	class __declspec(novtable) HUDMessagesModel
		: public BSTEventSink<HUDInventoryChangeMessageEvent>, // 000
		  public BSTEventSink<ShowHUDMessageEvent>,			   // 008
		  public BSTEventSink<ClearHUDMessagesEvent>,		   // 010
		  public BSTEventSink<HUDModeEvent>					   // 018
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDMessagesModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDMessagesModel };

		~HUDMessagesModel() override; // 00

		// override (BSTEventSink<HUDInventoryChangeMessageEvent>)
		BSEventNotifyControl ProcessEvent(const HUDInventoryChangeMessageEvent& a_event, BSTEventSource<HUDInventoryChangeMessageEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<ShowHUDMessageEvent>)
		BSEventNotifyControl ProcessEvent(const ShowHUDMessageEvent& a_event, BSTEventSource<ShowHUDMessageEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<ClearHUDMessagesEvent>)
		BSEventNotifyControl ProcessEvent(const ClearHUDMessagesEvent& a_event, BSTEventSource<ClearHUDMessagesEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<HUDModeEvent>)
		BSEventNotifyControl ProcessEvent(const HUDModeEvent& a_event, BSTEventSource<HUDModeEvent>* a_eventSource) override; // 01

		// members
		BSTValueEventSource<HUDMessageDisplayDataEvent> nextMessageData;				 // 020
		BSTValueEventSink<CanDisplayNextHUDMessage> canShowNextMessage;					 // 050
		BSTValueEventSink<HUDQuestVaultBoySwfName> questVaultBoySwfName;				 // 069
		BSTValueEventSink<HasHUDMessagesEvent> hasHUDMessages;							 // 090
		BSTValueEventSink<ShowingFeaturedItemVaultBoyEvent> showingFeaturedItemVaultBoy; // 0A8
		BSTObjectArena<ThrottleMessageData, BSTObjectArenaHeapAlloc, 8> throttles;		 // 0C0
		mutable BSSpinLock throttleArenaLock;											 // 0F8
		BSTObjectArena<ShowHUDMessageEvent, BSTObjectArenaHeapAlloc, 8> queuedMessages;	 // 100
		mutable BSSpinLock queuedMessagesLock;											 // 138
		HUDModes messagesHUDModes;														 // 140
	};
	static_assert(sizeof(HUDMessagesModel) == 0x160);
}
