#include "RE/B/BGSEntryPointFunctionDataBooleanGraphVariable.hpp"

namespace RE
{
	BGSEntryPointFunctionDataBooleanGraphVariable::BGSEntryPointFunctionDataBooleanGraphVariable()
	{
		REL::EmplaceVtable(this);
	}

	template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataBooleanGraphVariable>() const noexcept;
	template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataBooleanGraphVariable>() const noexcept;

	template BGSEntryPointFunctionDataBooleanGraphVariable* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataBooleanGraphVariable>() noexcept;
	template const BGSEntryPointFunctionDataBooleanGraphVariable* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataBooleanGraphVariable>() const noexcept;
}
