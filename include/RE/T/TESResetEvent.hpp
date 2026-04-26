#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESResetEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESResetEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESResetEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESResetEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref; // 00
	};
	static_assert(sizeof(TESResetEvent) == 0x08);
}
