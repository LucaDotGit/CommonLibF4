#pragma once

namespace RE
{
	enum class INPUT_EVENT_TYPE : std::int32_t
	{
		Button = 0,
		MouseMove = 1,
		CursorMove = 2,
		Char = 3,
		Thumbstick = 4,
		DeviceConnect = 5,
		Kinect = 6,
		None = 7
	};
}
