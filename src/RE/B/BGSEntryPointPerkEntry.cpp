#include "RE/B/BGSEntryPointPerkEntry.hpp"

namespace RE
{
	BGSEntryPointPerkEntry::BGSEntryPointPerkEntry()
	{
		REL::EmplaceVtable(this);
	}

	template bool BGSPerkEntry::Is<BGSEntryPointPerkEntry>() const noexcept;
	template bool BGSPerkEntry::IsNot<BGSEntryPointPerkEntry>() const noexcept;

	template BGSEntryPointPerkEntry* BGSPerkEntry::As<BGSEntryPointPerkEntry>() noexcept;
	template const BGSEntryPointPerkEntry* BGSPerkEntry::As<BGSEntryPointPerkEntry>() const noexcept;
}
