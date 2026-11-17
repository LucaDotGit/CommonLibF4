#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESFormIDRemapEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESFormIDRemapEvent>*
		{
			using FuncType = decltype(&TESFormIDRemapEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESFormIDRemapEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		TESFormID oldFormID; // 0x00
		TESFormID newFormID; // 0x04
	};

	static_assert(sizeof(TESFormIDRemapEvent) == 0x08);
}
