#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE::BGSCharacterMorph
{
	class BoneBaseScales
	{
	public:
		// members
		std::array<NiPoint3, 3> scales; // 00
	};
	static_assert(sizeof(BoneBaseScales) == 0x24);
}
