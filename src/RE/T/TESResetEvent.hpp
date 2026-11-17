#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESResetEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESResetEvent>*
		{
			using FuncType = decltype(&TESResetEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESResetEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref; // 0x00
	};

	static_assert(sizeof(TESResetEvent) == 0x08);
}
