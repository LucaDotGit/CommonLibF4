#include "RE/B/BGSEntryPointFunctionDataTwoValue.hpp"

namespace RE
{
	BGSEntryPointFunctionDataTwoValue::BGSEntryPointFunctionDataTwoValue()
	{
		REL::EmplaceVtable(this);
	}

	template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataTwoValue>() const noexcept;
	template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataTwoValue>() const noexcept;

	template BGSEntryPointFunctionDataTwoValue* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataTwoValue>() noexcept;
	template const BGSEntryPointFunctionDataTwoValue* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataTwoValue>() const noexcept;
}
