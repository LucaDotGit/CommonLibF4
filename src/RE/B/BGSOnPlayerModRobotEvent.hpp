#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSOnPlayerModRobotEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<BGSOnPlayerModRobotEvent>*
		{
			using FuncType = decltype(&BGSOnPlayerModRobotEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSOnPlayerModRobotEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> robotRef; // 0x00
		BGSMod::Attachment::Mod* mod;	   // 0x08
	};

	static_assert(sizeof(BGSOnPlayerModRobotEvent) == 0x10);
}
