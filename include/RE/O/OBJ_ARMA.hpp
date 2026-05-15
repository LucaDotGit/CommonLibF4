#pragma once

#include "RE/S/SEX.hpp"

namespace RE
{
	class OBJ_ARMA
	{
	public:
		// members
		std::array<std::int8_t, std::to_underlying(SEX::kTotal)> priorities;	// 00
		std::array<std::int8_t, std::to_underlying(SEX::kTotal)> modelRanges;	// 02
		std::array<std::int8_t, std::to_underlying(SEX::kTotal)> unusedArray04; // 04
		std::int8_t detectionSoundValue;										// 06
		REX::Float32 weaponAdjust;												// 08
	};
	static_assert(sizeof(OBJ_ARMA) == 0x0C);
}
