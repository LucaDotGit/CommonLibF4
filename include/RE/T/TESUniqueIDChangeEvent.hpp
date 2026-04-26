#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESUniqueIDChangeEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESUniqueIDChangeEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESUniqueIDChangeEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESUniqueIDChangeEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESFormID oldBaseFormID; // 00
		TESFormID newBaseFormID; // 04
		TESFormID objectFormID;	 // 08
		ContainerID oldUniqueID; // 0C
		ContainerID newUniqueID; // 0E
	};
	static_assert(sizeof(TESUniqueIDChangeEvent) == 0x10);
}
