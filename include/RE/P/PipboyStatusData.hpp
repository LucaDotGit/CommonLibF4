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
	class __declspec(novtable) PipboyStatusData
		: public PipboyDataGroup,							   // 00
		  public BSTEventSink<PlayerLifeStateChanged::Event>,  // 98
		  public BSTEventSink<PlayerInDialogueChanged::Event>, // A0
		  public BSTEventSink<MenuOpenCloseEvent>,			   // A8
		  public BSTEventSink<BGSInventoryListEvent::Event>,   // B0
		  public BSTEventSink<LoadingStatusChanged::Event>,	   // B8
		  public BSTEventSink<VATSEvents::ModeChange>,		   // C0
		  public BSTEventSink<UserEventEnabledEvent>		   // C8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyStatusData };
		inline static constexpr auto VTABLE{ VTABLE::PipboyStatusData };

		~PipboyStatusData() override;

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 02
		void DoClearData() override;		  // 03
		void DoClearSink() override;		  // 04

		// override (BSTEventSink<PlayerLifeStateChanged::Event>)
		BSEventNotifyControl ProcessEvent(const PlayerLifeStateChanged::Event& a_event, BSTEventSource<PlayerLifeStateChanged::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<PlayerInDialogueChanged::Event>)
		BSEventNotifyControl ProcessEvent(const PlayerInDialogueChanged::Event& a_event, BSTEventSource<PlayerInDialogueChanged::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSInventoryListEvent::Event>)
		BSEventNotifyControl ProcessEvent(const BGSInventoryListEvent::Event& a_event, BSTEventSource<BGSInventoryListEvent::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<LoadingStatusChanged::Event>)
		BSEventNotifyControl ProcessEvent(const LoadingStatusChanged::Event& a_event, BSTEventSource<LoadingStatusChanged::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<VATSEvents::ModeChange>)
		BSEventNotifyControl ProcessEvent(const VATSEvents::ModeChange& a_event, BSTEventSource<VATSEvents::ModeChange>* a_eventSource) override; // 01

		//
		BSEventNotifyControl ProcessEvent(const UserEventEnabledEvent& a_event, BSTEventSource<UserEventEnabledEvent>* a_eventSource) override; // 01

		// members
		PipboyObject* statusObject;
		PipboyArray* pipboyEffectColorArray;
	};
	static_assert(sizeof(PipboyStatusData) == 0xE0);
}
