#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class HolotapeChatterEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<HolotapeChatterEvent>* GetEventSource()
		{
			using FuncType = decltype(&HolotapeChatterEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::HolotapeChatterEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> npcRef;	  // 00
		BSFixedString chatter;				  // 08
		REX::Float32 numericData;			  // 10
		NiPointer<TESObjectREFR> holotapeRef; // 18
		TESFormID holotapeBaseFormID;		  // 20
		ContainerID holotapeUniqueID;		  // 24
	};
	static_assert(sizeof(HolotapeChatterEvent) == 0x28);
}
