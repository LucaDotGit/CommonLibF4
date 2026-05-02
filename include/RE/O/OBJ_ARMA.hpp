#pragma once

#include "RE/S/SEX.hpp"

namespace RE
{
	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
	class OBJ_ARMA
	{
	public:
		// members
		union
		{
			struct
			{
				std::int8_t malePriority;
				std::int8_t femalePriority;
			};
			std::array<std::int8_t, std::to_underlying(SEX::kTotal)> priorities{};
		}; // 00
		union
		{
			struct
			{
				std::int8_t maleModelRange;
				std::int8_t femaleModelRange;
			};
			std::array<std::int8_t, std::to_underlying(SEX::kTotal)> modelRanges{};
		}; // 02
		union
		{
			struct
			{
				std::int8_t unused04;
				std::int8_t unused05;
			};
			std::array<std::int8_t, std::to_underlying(SEX::kTotal)> unusedArray04{};
		}; // 04
		std::int8_t detectionSoundValue; // 06
		REX::Float32 weaponAdjust;		 // 08
	};
	static_assert(sizeof(OBJ_ARMA) == 0x0C);
}
