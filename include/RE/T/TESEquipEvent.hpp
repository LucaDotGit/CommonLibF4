#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESEquipEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESEquipEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESEquipEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESEquipEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> actorRef; // 00
		TESFormID baseItemFormID;		   // 08
		TESFormID itemRefFormID;		   // 0C
		ContainerID uniqueID;			   // 10
		bool equipped;					   // 12
	};
	static_assert(sizeof(TESEquipEvent) == 0x18);
}
