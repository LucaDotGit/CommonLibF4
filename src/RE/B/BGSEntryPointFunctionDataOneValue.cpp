#include "RE/B/BGSEntryPointFunctionDataOneValue.hpp"

namespace RE
{
	BGSEntryPointFunctionDataOneValue::BGSEntryPointFunctionDataOneValue()
	{
		REL::EmplaceVtable(this);
	}

	template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataOneValue>() const noexcept;
	template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataOneValue>() const noexcept;

	template BGSEntryPointFunctionDataOneValue* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataOneValue>() noexcept;
	template const BGSEntryPointFunctionDataOneValue* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataOneValue>() const noexcept;
}
