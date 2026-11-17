#include "RE/B/BGSEntryPointPerkEntry.hpp"

namespace RE
{
	BGSEntryPointPerkEntry::BGSEntryPointPerkEntry()
	{
		REL::EmplaceVtable(this);
	}

	BGSEntryPointPerkEntry::~BGSEntryPointPerkEntry() = default;
}
