#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class AutoLoadDoorRolloverData
	{
	public:
		// members
		ObjectRefHandle autoLoadDoor;		 // 0x00
		BGSLocalizedString doorRolloverName; // 0x08
	};

	static_assert(sizeof(AutoLoadDoorRolloverData) == 0x10);
}
