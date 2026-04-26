#pragma once

namespace RE
{
	enum class ITEM_REMOVE_REASON : std::int32_t
	{
		kNone = 0,
		kStealing = 1,
		kSelling = 2,
		KDropping = 3,
		kStoreContainer = 4,
		kStoreTeammate = 5
	};
}
