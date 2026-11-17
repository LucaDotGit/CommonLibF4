#include "RE/B/BGSEntryPointFunctionDataLeveledList.hpp"

namespace RE
{
	BGSEntryPointFunctionDataLeveledList::BGSEntryPointFunctionDataLeveledList()
	{
		REL::EmplaceVtable(this);
	}

	BGSEntryPointFunctionDataLeveledList::~BGSEntryPointFunctionDataLeveledList() = default;
}
