#pragma once

namespace RE
{
	enum class INPUT_DEVICE : std::int32_t
	{
		kNone = -1,
		kKeyboard = 0,
		kMouse = 1,
		kGamepad = 2,
		kKinect = 3,
		kVirtualKeyboard = 4,

		kSupported = 3,
		kTotal = 5
	};
}
