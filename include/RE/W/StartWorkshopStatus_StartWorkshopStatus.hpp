#pragma once

namespace RE::Workshop
{
	enum class StartWorkshopStatus : std::int32_t
	{
		kOk = 0,
		kNoNearbyWorkshop = 1,
		kAlreadyInWorkshopMode = 2,
		kActivationBlocked = 3
	};
}
