#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSOnPlayerCreateRobotEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<BGSOnPlayerCreateRobotEvent>* GetEventSource()
		{
			using FuncType = decltype(&BGSOnPlayerCreateRobotEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOnPlayerCreateRobotEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> robotRef; // 00
	};
	static_assert(sizeof(BGSOnPlayerCreateRobotEvent) == 0x08);
}
