#pragma once

namespace RE::Workshop
{
	enum class StartWorkshopStatus : std::int32_t
	{
		Ok = 0,
		NoNearbyWorkshop = 1,
		AlreadyInWorkshopMode = 2,
		ActivationBlocked = 3
	};
}
