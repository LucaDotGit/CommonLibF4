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
	class __declspec(novtable) MenuEventHandler :
		public BSTEventSink<MenuOpenCloseEvent>, // 0x00
		public BSTEventSink<LooksMenuEvent>,	 // 0x08
		public BSTEventSink<TutorialEvent>,		 // 0x10
		public BSTSingletonSDM<MenuEventHandler> // 0x18
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__MenuEventHandler;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__MenuEventHandler;

		~MenuEventHandler() override; // 0x00

		// override (BSTEventSink<MenuOpenCloseEvent>)
		auto ProcessEvent(
			const MenuOpenCloseEvent& a_event,
			BSTEventSource<MenuOpenCloseEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<LooksMenuEvent>)
		auto ProcessEvent(const LooksMenuEvent& a_event, BSTEventSource<LooksMenuEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TutorialEvent>)
		auto ProcessEvent(const TutorialEvent& a_event, BSTEventSource<TutorialEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> MenuEventHandler*
		{
			static const auto SINGLETON =
				REL::Relocation<MenuEventHandler**>{ID::GameScript::MenuEventHandler::Singleton};
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm;														   // 0x20
		mutable BSSpinLock menuOpenCloseLock;																   // 0x28
		BSTHashMap<BSFixedString, BSTSmartPointer<Internal::EventRegistrationObjectList>> menuOpenCloseEvents; // 0x30
		mutable BSSpinLock looksMenuEventLock;																   // 0x60
		BSTHashMap<BSFixedString, BSTSmartPointer<Internal::EventRegistrationObjectList>> looksMenuEvents;	   // 0x68
		mutable BSSpinLock tutorialEventLock;																   // 0x98
		BSTHashMap<BSFixedString, BSTSmartPointer<Internal::EventRegistrationObjectList>> tutorialEvents;	   // 0xA0
	};

	static_assert(sizeof(MenuEventHandler) == 0xD0);
}
