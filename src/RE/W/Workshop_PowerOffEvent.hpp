#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class PowerOffEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<PowerOffEvent>*
		{
			using FuncType = decltype(&PowerOffEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::PowerOffEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> itemRef; // 0x00
	};

	static_assert(sizeof(PowerOffEvent) == 0x08);
}
