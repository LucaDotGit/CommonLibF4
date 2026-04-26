#pragma once

namespace RE
{
	enum class EntryPointFunctionType : std::int32_t
	{
		kInvalid = 0,
		kOneValue = 1,
		kTwoValue = 2,
		kLeveledList = 3,
		kActivateChoice = 4,
		kSpellItem = 5,
		kBooleanGraphVariable = 6,
		kText = 7,
		kActorValue = 8
	};
}
