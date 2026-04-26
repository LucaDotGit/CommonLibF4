#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class BGSOnPlayerModArmorWeaponEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<BGSOnPlayerModArmorWeaponEvent>* GetEventSource()
		{
			using FuncType = decltype(&BGSOnPlayerModArmorWeaponEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOnPlayerModArmorWeaponEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESBoundObject* weapon;		  // 00
		BGSMod::Attachment::Mod* mod; // 08
	};
	static_assert(sizeof(BGSOnPlayerModArmorWeaponEvent) == 0x10);
}
