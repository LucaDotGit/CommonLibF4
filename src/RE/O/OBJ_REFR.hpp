#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class OBJ_REFR
	{
	public:
		// members
		NiPoint3A angle;				 // 0x00
		NiPoint3A location;				 // 0x10
		TESBoundObject* objectReference; // 0x20
	};

	static_assert(sizeof(OBJ_REFR) == 0x30);
}
