#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESUniqueIDChangeEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESUniqueIDChangeEvent>*
		{
			using FuncType = decltype(&TESUniqueIDChangeEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESUniqueIDChangeEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		TESFormID oldBaseFormID; // 0x00
		TESFormID newBaseFormID; // 0x04
		TESFormID objectFormID;	 // 0x08
		ContainerID oldUniqueID; // 0x0C
		ContainerID newUniqueID; // 0x0E
	};

	static_assert(sizeof(TESUniqueIDChangeEvent) == 0x10);
}
