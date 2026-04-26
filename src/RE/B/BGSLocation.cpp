#include "RE/B/BGSLocation.hpp"

namespace RE
{
	auto BGSLocation::GetLinkedLocations() -> BSTHashMap<TESFormID, BSTArray<BSTPair<TESFormID, TESFormID>>*>&
	{
		static const auto LINKED_LOCATIONS = REL::Relocation<BSTHashMap<TESFormID, BSTArray<BSTPair<TESFormID, TESFormID>>*>*>{ ID::BGSLocation::LinkedLocations, Offset::BGSLocation::LinkedLocations };
		return *LINKED_LOCATIONS;
	}

	bool BGSLocation::IsChildOf(const BGSLocation* a_parent) const
	{
		if (!a_parent) {
			return false;
		}

		for (const auto* locIt = this; locIt; locIt = locIt->parentLoc) {
			if (locIt == a_parent) {
				return true;
			}
		}

		return false;
	}

	bool BGSLocation::IsParentOf(const BGSLocation* a_child) const
	{
		if (!a_child) {
			return false;
		}

		for (const auto* locIt = a_child; locIt; locIt = locIt->parentLoc) {
			if (locIt == this) {
				return true;
			}
		}

		return false;
	}
}
