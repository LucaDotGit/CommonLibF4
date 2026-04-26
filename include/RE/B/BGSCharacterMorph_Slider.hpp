#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::BGSCharacterMorph
{
	class Slider
	{
	public:
		// members
		std::array<BSFixedString, 2> morphNames; // 00
		std::uint32_t uniqueID{ 0 };			 // 10
	};
	static_assert(sizeof(Slider) == 0x18);
}
