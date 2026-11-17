#pragma once

namespace RE
{
	enum class CameraStates : std::int32_t
	{
		FirstPerson = 0,
		AutoVanity = 1,
		VATS = 2,
		Free = 3,
		IronSights = 4,
		PCTransition = 5,
		Tween = 6,
		Animated = 7,
		ThirdPerson = 8,
		Furniture = 9,
		Mount = 10,
		Bleedout = 11,
		Dialogue = 12,

		_Min = FirstPerson,
		_Max = Dialogue,

		_Count = _Max + 1
	};
}
