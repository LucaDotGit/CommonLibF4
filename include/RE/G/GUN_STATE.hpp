#pragma once

namespace RE
{
	enum class GUN_STATE : std::uint32_t
	{
		kDrawn = 0,
		kRelaxed = 1,
		kBlocked = 2,
		kAlert = 3,
		kReloading = 4,
		kThrowing = 5,
		kSighted = 6,
		kFire = 7,
		kFireSighted = 8
	};
}
