#pragma once

#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint4.hpp"

namespace RE
{
	class BSTransformDeltaEvent
	{
	public:
		// members
		NiMatrix3 deltaRotation;	  // 0x00
		NiPoint4 deltaTranslation;	  // 0x30
		NiPoint4 previousTranslation; // 0x40
		NiPoint4 previousRotation;	  // 0x50
		NiPoint4 previousScale;		  // 0x60
		NiPoint4 currentTranslation;  // 0x70
		NiPoint4 currentRotation;	  // 0x80
		NiPoint4 currentScale;		  // 0x90
	};

	static_assert(sizeof(BSTransformDeltaEvent) == 0xA0);
}
