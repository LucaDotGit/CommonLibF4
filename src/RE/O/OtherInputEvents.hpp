#pragma once

namespace RE::OtherInputEvents
{
	enum class OTHER_EVENT_FLAG : std::uint32_t
	{
		JournalTabs = 1 << 0,
		Activation = 1 << 1,
		FastTravel = 1 << 2,
		POVChange = 1 << 3,
		VATS = 1 << 4,
		Favorites = 1 << 5,
		PipboyLight = 1 << 6,
		ZKey = 1 << 7,
		Running = 1 << 8,
		Cursor = 1 << 9,
		Sprinting = 1 << 10,

		All = std::numeric_limits<std::underlying_type_t<OTHER_EVENT_FLAG>>::max()
	};
}
