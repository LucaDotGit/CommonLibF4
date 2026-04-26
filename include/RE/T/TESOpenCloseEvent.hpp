#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESOpenCloseEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESOpenCloseEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESOpenCloseEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESOpenCloseEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> sourceRef; // 00
		NiPointer<TESObjectREFR> targetRef; // 08
		bool opened;						// 10
	};
	static_assert(sizeof(TESOpenCloseEvent) == 0x18);
}
