#include "RE/B/BGSEntryPointFunctionDataLeveledList.hpp"

namespace RE
{
	BGSEntryPointFunctionDataLeveledList::BGSEntryPointFunctionDataLeveledList()
	{
		REL::EmplaceVtable(this);
	}

	template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataLeveledList>() const noexcept;
	template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataLeveledList>() const noexcept;

	template BGSEntryPointFunctionDataLeveledList* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataLeveledList>() noexcept;
	template const BGSEntryPointFunctionDataLeveledList* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataLeveledList>() const noexcept;
}
