#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESEquipEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESEquipEvent>*
		{
			using FuncType = decltype(&TESEquipEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESEquipEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> actorRef; // 0x00
		TESFormID baseItemFormID;		   // 0x08
		TESFormID itemRefFormID;		   // 0x0C
		ContainerID uniqueID;			   // 0x10
		bool equipped;					   // 0x12
	};

	static_assert(sizeof(TESEquipEvent) == 0x18);
}
