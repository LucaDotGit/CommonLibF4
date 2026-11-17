#pragma once

namespace RE
{
	enum class INPUT_DEVICE : std::int32_t
	{
		None = -1,
		Keyboard = 0,
		Mouse = 1,
		Gamepad = 2,
		Kinect = 3,
		VirtualKeyboard = 4,

		Supported = 3,
		_Count = 5
	};
}
