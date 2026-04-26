#pragma once

namespace RE
{
	enum class COMMAND_TYPE : std::int32_t
	{
		kNone = 0,
		kCall = 1,
		kFollow = 2,
		kMove = 3,
		kAttack = 4,
		kInspect = 5,
		kRetrieve = 6,
		kStay = 7,
		kRelease = 8,
		kHeal = 9,
		kAssign = 10,
		kRide = 11,
		kEnter = 12
	};
}
