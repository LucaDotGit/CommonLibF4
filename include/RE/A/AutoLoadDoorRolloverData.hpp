#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class AutoLoadDoorRolloverData
	{
	public:
		// members
		ObjectRefHandle autoLoadDoor;		 // 00
		BGSLocalizedString doorRolloverName; // 08
	};
	static_assert(sizeof(AutoLoadDoorRolloverData) == 0x10);
}
