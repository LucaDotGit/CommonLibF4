#pragma once

#include "RE/A/AITimeStamp.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class DetectionEvent
	{
	public:
		// members
		std::uint32_t actionValue; // 0x00
		NiPoint3 location;		   // 0x04
		AITimeStamp timeStamp;	   // 0x10
		ObjectRefHandle ref;	   // 0x14
	};

	static_assert(sizeof(DetectionEvent) == 0x18);
}
