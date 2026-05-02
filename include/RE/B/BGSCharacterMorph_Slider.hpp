#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/S/SEX.hpp"

namespace RE::BGSCharacterMorph
{
	class Slider
	{
	public:
		~Slider()
		{
			for (auto& morphName : morphNames) {
				morphName.~BSFixedString();
			}
		}

		// members
		union
		{
			struct
			{
				BSFixedString maleMorphName;
				BSFixedString femaleMorphName;
			};
			std::array<BSFixedString, std::to_underlying(SEX::kTotal)> morphNames{};
		}; // 00
		std::uint32_t uniqueID; // 10
	};
	static_assert(sizeof(Slider) == 0x18);
}
