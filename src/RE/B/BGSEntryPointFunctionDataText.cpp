#include "RE/B/BGSEntryPointFunctionDataText.hpp"

namespace RE
{
	BGSEntryPointFunctionDataText::BGSEntryPointFunctionDataText()
	{
		REL::EmplaceVtable(this);
	}

	template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataText>() const noexcept;
	template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataText>() const noexcept;

	template BGSEntryPointFunctionDataText* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataText>() noexcept;
	template const BGSEntryPointFunctionDataText* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataText>() const noexcept;
}
