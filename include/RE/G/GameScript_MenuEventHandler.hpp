#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class LooksMenuEvent;
	class MenuOpenCloseEvent;
	class TutorialEvent;
}

namespace RE::BSScript
{
	class IVirtualMachine;
}

namespace RE::GameScript::Internal
{
	class EventRegistrationObjectList;
}

namespace RE::GameScript
{
	class __declspec(novtable) MenuEventHandler
		: public BSTEventSink<MenuOpenCloseEvent>, // 00
		  public BSTEventSink<LooksMenuEvent>,	   // 08
		  public BSTEventSink<TutorialEvent>,	   // 10
		  public BSTSingletonSDM<MenuEventHandler> // 18
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__MenuEventHandler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__MenuEventHandler };

		~MenuEventHandler() override; // 00

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<LooksMenuEvent>)
		BSEventNotifyControl ProcessEvent(const LooksMenuEvent& a_event, BSTEventSource<LooksMenuEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TutorialEvent>)
		BSEventNotifyControl ProcessEvent(const TutorialEvent& a_event, BSTEventSource<TutorialEvent>* a_eventSource) override; // 01

		[[nodiscard]] static MenuEventHandler* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<MenuEventHandler**>{ ID::GameScript::MenuEventHandler::Singleton };
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm;														   // 20
		mutable BSSpinLock menuOpenCloseLock;																   // 28
		BSTHashMap<BSFixedString, BSTSmartPointer<Internal::EventRegistrationObjectList>> menuOpenCloseEvents; // 30
		mutable BSSpinLock looksMenuEventLock;																   // 60
		BSTHashMap<BSFixedString, BSTSmartPointer<Internal::EventRegistrationObjectList>> looksMenuEvents;	   // 68
		mutable BSSpinLock tutorialEventLock;																   // 98
		BSTHashMap<BSFixedString, BSTSmartPointer<Internal::EventRegistrationObjectList>> tutorialEvents;	   // A0
	};
	static_assert(sizeof(MenuEventHandler) == 0xD0);
}
