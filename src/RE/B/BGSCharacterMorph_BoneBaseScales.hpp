#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE::BGSCharacterMorph
{
	class BoneBaseScales
	{
	public:
		// members
		std::array<NiPoint3, 3> scales; // 0x00
	};

	static_assert(sizeof(BoneBaseScales) == 0x24);
}
