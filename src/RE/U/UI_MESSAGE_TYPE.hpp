#pragma once

namespace RE
{
	enum class UI_MESSAGE_TYPE : std::int32_t
	{
		Update = 0,
		Show = 1,
		Reshow = 2,
		Hide = 3,
		ForceHide = 4,
		ScaleformEvent = 5,
		UserEvent = 6,
		InventoryUpdate = 7,
		UserProfileChange = 8,
		MUStatusChange = 9,
		ResumeCaching = 10,
		UpdateController = 11,
		ChatterEvent = 12,

		_Count = 13
	};
}
