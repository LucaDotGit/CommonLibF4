#pragma once

namespace RE::OtherInputEvents
{
	enum class OTHER_EVENT_FLAG : std::uint32_t
	{
		kAll = std::numeric_limits<std::underlying_type_t<OTHER_EVENT_FLAG>>::max(),

		kJournalTabs = 1 << 0,
		kActivation = 1 << 1,
		kFastTravel = 1 << 2,
		kPOVChange = 1 << 3,
		kVATS = 1 << 4,
		kFavorites = 1 << 5,
		kPipboyLight = 1 << 6,
		kZKey = 1 << 7,
		kRunning = 1 << 8,
		kCursor = 1 << 9,
		kSprinting = 1 << 10
	};
}
