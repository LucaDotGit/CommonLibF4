#pragma once

namespace RE
{
	enum class CONDITIONITEMOBJECT : std::int32_t
	{
		Self = 0,
		Target = 1,
		Ref = 2,
		CombatTarget = 3,
		LinkedRef = 4,
		QuestAlias = 5,
		PackData = 6,
		EventData = 7,
		CommandTarget = 8,
		EventCameraRef = 9,
		MyKiller = 10
	};
}
