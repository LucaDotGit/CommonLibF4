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
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TerminalMenuItemRunEvent>*
		{
			using FuncType = decltype(&TerminalMenuItemRunEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TerminalMenuItemRunEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		BSTSmartPointer<REFREventCallbacks::IEventCallback> callback; // 0x00
		TESObjectREFR* targetRef;									  // 0x08
		TESFormID terminalFormID;									  // 0x10
		std::uint16_t menuItemID;									  // 0x14
	};

	static_assert(sizeof(TerminalMenuItemRunEvent) == 0x18);
}
