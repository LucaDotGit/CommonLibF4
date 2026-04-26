#pragma once

namespace RE
{
	enum class CONDITIONITEMOBJECT : std::int32_t
	{
		kSelf = 0,
		kTarget = 1,
		kRef = 2,
		kCombatTarget = 3,
		kLinkedRef = 4,
		kQuestAlias = 5,
		kPackData = 6,
		kEventData = 7,
		kCommandTarget = 8,
		kEventCameraRef = 9,
		kMyKiller = 10
	};
}
