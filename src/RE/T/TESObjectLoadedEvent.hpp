#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESObjectLoadedEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESObjectLoadedEvent>*
		{
			using FuncType = decltype(&TESObjectLoadedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectLoadedEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		TESFormID formID; // 0x00
		bool loaded;	  // 0x04
	};

	static_assert(sizeof(TESObjectLoadedEvent) == 0x08);
}
