#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE::BGSCharacterMorph
{
	class Transform
	{
	public:
		// members
		NiPoint3 position; // 00
		NiPoint3 rotation; // 0C
		NiPoint3 scale;	   // 18
	};
	static_assert(sizeof(Transform) == 0x24);
}
