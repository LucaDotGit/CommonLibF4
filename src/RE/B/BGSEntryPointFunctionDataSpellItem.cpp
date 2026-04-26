#include "RE/B/BGSEntryPointFunctionDataSpellItem.hpp"

namespace RE
{
	BGSEntryPointFunctionDataSpellItem::BGSEntryPointFunctionDataSpellItem()
	{
		REL::EmplaceVtable(this);
	}

	template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataSpellItem>() const noexcept;
	template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataSpellItem>() const noexcept;

	template BGSEntryPointFunctionDataSpellItem* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataSpellItem>() noexcept;
	template const BGSEntryPointFunctionDataSpellItem* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataSpellItem>() const noexcept;
}
