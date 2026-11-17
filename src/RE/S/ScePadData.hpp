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
		std::uint32_t buttons;						   // 0x00
		ScePadAnalogStick leftStick;				   // 0x04
		ScePadAnalogStick rightStick;				   // 0x06
		ScePadAnalogButtons analogButtons;			   // 0x08
		SceFQuaternion orientation;					   // 0x0C
		SceFVector3 acceleration;					   // 0x1C
		SceFVector3 angularVelocity;				   // 0x28
		ScePadTouchData touchData;					   // 0x34
		bool connected;								   // 0x4C
		std::uint64_t timestamp;					   // 0x50
		ScePadExtensionUnitData extensionUnitData;	   // 0x58
		std::uint8_t connectedCount;				   // 0x68
		std::array<std::uint8_t, 2> reserve;		   // 0x69
		std::uint8_t deviceUniqueDataLen;			   // 0x6B
		std::array<std::uint8_t, 12> deviceUniqueData; // 0x6C
	};

	static_assert(sizeof(ScePadData) == 0x78);
}
