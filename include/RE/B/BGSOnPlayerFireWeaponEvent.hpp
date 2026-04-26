#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class BGSOnPlayerFireWeaponEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<BGSOnPlayerFireWeaponEvent>* GetEventSource()
		{
			using FuncType = decltype(&BGSOnPlayerFireWeaponEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOnPlayerFireWeaponEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESBoundObject* weapon; // 00
	};
	static_assert(sizeof(BGSOnPlayerFireWeaponEvent) == 0x08);
}
