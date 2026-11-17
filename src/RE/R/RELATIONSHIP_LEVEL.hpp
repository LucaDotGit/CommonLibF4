#pragma once

namespace RE
{
	enum class RELATIONSHIP_LEVEL : std::int32_t
	{
		Lover = 0,
		Ally = 1,
		Confidant = 2,
		Friend = 3,
		Acquaintance = 4,
		Rival = 5,
		Foe = 6,
		Enemy = 7,
		Archnemesis = 8,

		_Count = 9
	};
}
