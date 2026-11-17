#pragma once

namespace RE
{
	enum class EntryPointFunctionType : std::int32_t
	{
		Invalid = 0,
		OneValue = 1,
		TwoValue = 2,
		LeveledList = 3,
		ActivateChoice = 4,
		SpellItem = 5,
		BooleanGraphVariable = 6,
		Text = 7,
		ActorValue = 8
	};
}
