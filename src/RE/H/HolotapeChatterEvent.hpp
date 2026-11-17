#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class HolotapeChatterEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<HolotapeChatterEvent>*
		{
			using FuncType = decltype(&HolotapeChatterEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::HolotapeChatterEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> npcRef;	  // 0x00
		BSFixedString chatter;				  // 0x08
		REX::Float32 numericData;			  // 0x10
		NiPointer<TESObjectREFR> holotapeRef; // 0x18
		TESFormID holotapeBaseFormID;		  // 0x20
		ContainerID holotapeUniqueID;		  // 0x24
	};

	static_assert(sizeof(HolotapeChatterEvent) == 0x28);
}
