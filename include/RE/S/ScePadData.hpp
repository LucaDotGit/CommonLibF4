#pragma once

#include "RE/S/SceFQuaternion.hpp"
#include "RE/S/SceFVector3.hpp"
#include "RE/S/ScePadAnalogButtons.hpp"
#include "RE/S/ScePadAnalogStick.hpp"
#include "RE/S/ScePadExtensionUnitData.hpp"
#include "RE/S/ScePadTouchData.hpp"

namespace RE
{
	class ScePadData
	{
	public:
		// members
		std::uint32_t buttons;						   // 00
		ScePadAnalogStick leftStick;				   // 04
		ScePadAnalogStick rightStick;				   // 06
		ScePadAnalogButtons analogButtons;			   // 08
		SceFQuaternion orientation;					   // 0C
		SceFVector3 acceleration;					   // 1C
		SceFVector3 angularVelocity;				   // 28
		ScePadTouchData touchData;					   // 34
		bool connected;								   // 4C
		std::uint64_t timestamp;					   // 50
		ScePadExtensionUnitData extensionUnitData;	   // 58
		std::uint8_t connectedCount;				   // 68
		std::array<std::uint8_t, 2> reserve;		   // 69
		std::uint8_t deviceUniqueDataLen;			   // 6B
		std::array<std::uint8_t, 12> deviceUniqueData; // 6C
	};
	static_assert(sizeof(ScePadData) == 0x78);
}
