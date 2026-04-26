#include "RE/B/BGSAbilityPerkEntry.hpp"

namespace RE
{
	BGSAbilityPerkEntry::BGSAbilityPerkEntry()
	{
		REL::EmplaceVtable(this);
	}

	template bool BGSPerkEntry::Is<BGSAbilityPerkEntry>() const noexcept;
	template bool BGSPerkEntry::IsNot<BGSAbilityPerkEntry>() const noexcept;

	template BGSAbilityPerkEntry* BGSPerkEntry::As<BGSAbilityPerkEntry>() noexcept;
	template const BGSAbilityPerkEntry* BGSPerkEntry::As<BGSAbilityPerkEntry>() const noexcept;
}
