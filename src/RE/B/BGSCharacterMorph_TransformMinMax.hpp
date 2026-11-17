#pragma once

#include "RE/B/BGSCharacterMorph_Transform.hpp"

namespace RE::BGSCharacterMorph
{
	class TransformMinMax
	{
	public:
		// members
		Transform minima; // 0x00
		Transform maxima; // 0x24
	};

	static_assert(sizeof(TransformMinMax) == 0x48);
}
