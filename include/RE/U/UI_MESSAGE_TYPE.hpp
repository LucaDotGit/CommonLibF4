#pragma once

namespace RE
{
	enum class UI_MESSAGE_TYPE : std::int32_t
	{
		kUpdate = 0,
		kShow = 1,
		kReshow = 2,
		kHide = 3,
		kForceHide = 4,
		kScaleformEvent = 5,
		kUserEvent = 6,
		kInventoryUpdate = 7,
		kUserProfileChange = 8,
		kMUStatusChange = 9,
		kResumeCaching = 10,
		kUpdateController = 11,
		kChatterEvent = 12,

		kTotal = 13
	};
}
