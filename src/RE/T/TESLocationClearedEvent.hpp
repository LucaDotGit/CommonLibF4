#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESLocationClearedEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESLocationClearedEvent>*
		{
			using FuncType = decltype(&TESLocationClearedEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESLocationClearedEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		BGSLocation* location; // 0x00
	};

	static_assert(sizeof(TESLocationClearedEvent) == 0x08);
}
