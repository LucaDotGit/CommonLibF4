#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class BGSOnPlayerModArmorWeaponEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<BGSOnPlayerModArmorWeaponEvent>*
		{
			using FuncType = decltype(&BGSOnPlayerModArmorWeaponEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSOnPlayerModArmorWeaponEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		TESBoundObject* weapon;		  // 0x00
		BGSMod::Attachment::Mod* mod; // 0x08
	};

	static_assert(sizeof(BGSOnPlayerModArmorWeaponEvent) == 0x10);
}
