#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/S/SEX.hpp"

namespace RE::BGSCharacterMorph
{
	class Slider
	{
	public:
		// members
		std::array<BSFixedString, std::to_underlying(SEX::_Count)> morphNames; // 0x00
		std::uint32_t uniqueID{0};											   // 0x10
	};

	static_assert(sizeof(Slider) == 0x18);
}
