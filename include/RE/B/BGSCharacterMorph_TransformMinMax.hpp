#pragma once

#include "RE/B/BGSCharacterMorph_Transform.hpp"

namespace RE::BGSCharacterMorph
{
	class TransformMinMax
	{
	public:
		// members
		Transform minima; // 00
		Transform maxima; // 24
	};
	static_assert(sizeof(TransformMinMax) == 0x48);
}
