#include "RE/B/BGSQuestPerkEntry.hpp"

namespace RE
{
	BGSQuestPerkEntry::BGSQuestPerkEntry()
	{
		REL::EmplaceVtable(this);
	}

	template bool BGSPerkEntry::Is<BGSQuestPerkEntry>() const noexcept;
	template bool BGSPerkEntry::IsNot<BGSQuestPerkEntry>() const noexcept;

	template BGSQuestPerkEntry* BGSPerkEntry::As<BGSQuestPerkEntry>() noexcept;
	template const BGSQuestPerkEntry* BGSPerkEntry::As<BGSQuestPerkEntry>() const noexcept;
}
