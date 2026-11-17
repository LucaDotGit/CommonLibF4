#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE::BGSCharacterMorph
{
	class Transform
	{
	public:
		// members
		NiPoint3 position; // 0x00
		NiPoint3 rotation; // 0x0C
		NiPoint3 scale;	   // 0x18
	};

	static_assert(sizeof(Transform) == 0x24);
}
