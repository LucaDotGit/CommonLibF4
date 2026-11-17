#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/P/PipboyDataGroup.hpp"

namespace RE
{
	class MenuOpenCloseEvent;
	class UserEventEnabledEvent;
}

namespace RE::BGSInventoryListEvent
{
	class Event;
}

namespace RE::LoadingStatusChanged
{
	class Event;
}

namespace RE::PlayerInDialogueChanged
{
	class Event;
}

namespace RE::PlayerLifeStateChanged
{
	class Event;
}

namespace RE::VATSEvents
{
	class ModeChange;
}

namespace RE
{
	class __declspec(novtable) PipboyStatusData :
		public PipboyDataGroup,								 // 0x00
		public BSTEventSink<PlayerLifeStateChanged::Event>,	 // 0x98
		public BSTEventSink<PlayerInDialogueChanged::Event>, // 0xA0
		public BSTEventSink<MenuOpenCloseEvent>,			 // 0xA8
		public BSTEventSink<BGSInventoryListEvent::Event>,	 // 0xB0
		public BSTEventSink<LoadingStatusChanged::Event>,	 // 0xB8
		public BSTEventSink<VATSEvents::ModeChange>,		 // 0xC0
		public BSTEventSink<UserEventEnabledEvent>			 // 0xC8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyStatusData;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyStatusData;

		~PipboyStatusData() override; // 0x00

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 0x02
		void DoClearData() override;		  // 0x03
		void DoClearSink() override;		  // 0x04

		// override (BSTEventSink<PlayerLifeStateChanged::Event>)
		auto ProcessEvent(
			const PlayerLifeStateChanged::Event& a_event,
			BSTEventSource<PlayerLifeStateChanged::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PlayerInDialogueChanged::Event>)
		auto ProcessEvent(
			const PlayerInDialogueChanged::Event& a_event,
			BSTEventSource<PlayerInDialogueChanged::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<MenuOpenCloseEvent>)
		auto ProcessEvent(
			const MenuOpenCloseEvent& a_event,
			BSTEventSource<MenuOpenCloseEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSInventoryListEvent::Event>)
		auto ProcessEvent(
			const BGSInventoryListEvent::Event& a_event,
			BSTEventSource<BGSInventoryListEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<LoadingStatusChanged::Event>)
		auto ProcessEvent(
			const LoadingStatusChanged::Event& a_event,
			BSTEventSource<LoadingStatusChanged::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<VATSEvents::ModeChange>)
		auto ProcessEvent(
			const VATSEvents::ModeChange& a_event,
			BSTEventSource<VATSEvents::ModeChange>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		//
		auto ProcessEvent(
			const UserEventEnabledEvent& a_event,
			BSTEventSource<UserEventEnabledEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// members
		PipboyObject* statusObject;
		PipboyArray* pipboyEffectColorArray;
	};

	static_assert(sizeof(PipboyStatusData) == 0xE0);
}
