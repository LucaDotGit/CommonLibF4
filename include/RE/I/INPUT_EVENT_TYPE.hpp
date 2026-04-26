#pragma once

namespace RE
{
	enum class INPUT_EVENT_TYPE : std::int32_t
	{
		kButton = 0,
		kMouseMove = 1,
		kCursorMove = 2,
		kChar = 3,
		kThumbstick = 4,
		kDeviceConnect = 5,
		kKinect = 6,
		kNone = 7
	};
}
