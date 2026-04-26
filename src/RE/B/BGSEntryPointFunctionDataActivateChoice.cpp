#include "RE/B/BGSEntryPointFunctionDataActivateChoice.hpp"

namespace RE
{
	BGSEntryPointFunctionDataActivateChoice::BGSEntryPointFunctionDataActivateChoice()
	{
		REL::EmplaceVtable(this);
	}

	template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataActivateChoice>() const noexcept;
	template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataActivateChoice>() const noexcept;

	template BGSEntryPointFunctionDataActivateChoice* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataActivateChoice>() noexcept;
	template const BGSEntryPointFunctionDataActivateChoice* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataActivateChoice>() const noexcept;
}
