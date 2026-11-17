#pragma once

namespace RE
{
	enum class ACQUIRE_TYPE : std::int32_t
	{
		None = -1,
		AlreadyHeld = 0,
		NoOwned_Ground = 1,
		NoOwned_Container = 2,
		BuyNPC = 3,
		StealGround = 4,
		Pickpocket = 5,
		Kill = 6,

		_Count = 7
	};
}
