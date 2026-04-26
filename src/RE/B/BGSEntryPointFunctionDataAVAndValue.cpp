#include "RE/B/BGSEntryPointFunctionDataAVAndValue.hpp"

namespace RE
{
	BGSEntryPointFunctionDataAVAndValue::BGSEntryPointFunctionDataAVAndValue()
	{
		REL::EmplaceVtable(this);
	}

	template bool BGSEntryPointFunctionData::Is<BGSEntryPointFunctionDataAVAndValue>() const noexcept;
	template bool BGSEntryPointFunctionData::IsNot<BGSEntryPointFunctionDataAVAndValue>() const noexcept;

	template BGSEntryPointFunctionDataAVAndValue* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataAVAndValue>() noexcept;
	template const BGSEntryPointFunctionDataAVAndValue* BGSEntryPointFunctionData::As<BGSEntryPointFunctionDataAVAndValue>() const noexcept;
}
