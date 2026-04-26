#pragma once

#include "RE/B/BSTHashMap.hpp"

namespace RE::BGSMod::Attachment
{
	[[nodiscard]] inline auto GetAllLooseMods() noexcept -> BSTHashMap<const Mod*, TESObjectMISC*>&
	{
		static const auto LOOSE_MOD_MAP = REL::Relocation<BSTHashMap<const Mod*, TESObjectMISC*>*>{ ID::BGSMod::Attachment::LooseModMap, Offset::BGSMod::Attachment::LooseModMap };
		return *LOOSE_MOD_MAP;
	}
}
