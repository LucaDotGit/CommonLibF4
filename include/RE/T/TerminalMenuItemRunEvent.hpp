#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::REFREventCallbacks
{
	class IEventCallback;
}

namespace RE
{
	class TerminalMenuItemRunEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TerminalMenuItemRunEvent>* GetEventSource()
		{
			using FuncType = decltype(&TerminalMenuItemRunEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TerminalMenuItemRunEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		BSTSmartPointer<REFREventCallbacks::IEventCallback> callback; // 00
		TESObjectREFR* targetRef;									  // 08
		TESFormID terminalFormID;									  // 10
		std::uint16_t menuItemID;									  // 14
	};
	static_assert(sizeof(TerminalMenuItemRunEvent) == 0x18);
}
