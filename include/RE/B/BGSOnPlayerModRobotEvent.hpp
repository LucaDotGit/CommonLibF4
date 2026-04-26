#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSOnPlayerModRobotEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<BGSOnPlayerModRobotEvent>* GetEventSource()
		{
			using FuncType = decltype(&BGSOnPlayerModRobotEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOnPlayerModRobotEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> robotRef; // 00
		BGSMod::Attachment::Mod* mod;	   // 08
	};
	static_assert(sizeof(BGSOnPlayerModRobotEvent) == 0x10);
}
