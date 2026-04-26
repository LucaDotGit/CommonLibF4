#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class HolotapePlayEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<HolotapePlayEvent>* GetEventSource()
		{
			using FuncType = decltype(&HolotapePlayEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::HolotapePlayEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> holotapeOriginRef; // 00
		NiPointer<TESObjectREFR> tapeRef;			// 08
		TESFormID holotapeBaseFormID;				// 10
		TESFormID holotapeRefFormID;				// 14
	};
	static_assert(sizeof(HolotapePlayEvent) == 0x18);
}
