#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class HolotapePlayEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<HolotapePlayEvent>*
		{
			using FuncType = decltype(&HolotapePlayEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::HolotapePlayEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> holotapeOriginRef; // 0x00
		NiPointer<TESObjectREFR> terminalRef;		// 0x08
		TESFormID holotapeBaseFormID;				// 0x10
		ContainerID holotapeRefUniqueID;			// 0x14
	};

	static_assert(sizeof(HolotapePlayEvent) == 0x18);
}
