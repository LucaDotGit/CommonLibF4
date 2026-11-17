#pragma once

#include "RE/S/SEX.hpp"

namespace RE
{
	class OBJ_ARMA
	{
	public:
		// members
		std::array<std::int8_t, std::to_underlying(SEX::_Count)> priorities;  // 0x00
		std::array<std::int8_t, std::to_underlying(SEX::_Count)> modelRanges; // 0x02
		std::array<std::int8_t, std::to_underlying(SEX::_Count)> unused04;	  // 0x04
		std::int8_t detectionSoundValue;									  // 0x06
		REX::Float32 weaponAdjust;											  // 0x08
	};

	static_assert(sizeof(OBJ_ARMA) == 0x0C);
}
