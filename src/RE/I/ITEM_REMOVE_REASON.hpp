#pragma once

namespace RE
{
	enum class ITEM_REMOVE_REASON : std::int32_t
	{
		None = 0,
		Stealing = 1,
		Selling = 2,
		KDropping = 3,
		StoreContainer = 4,
		StoreTeammate = 5
	};
}
