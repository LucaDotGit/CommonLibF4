#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class WeatherEntry
	{
	public:
		GAME_HEAP_REDEFINE_NEW(WeatherEntry);

		// members
		TESWeather* weather;  // 00
		std::uint32_t chance; // 08
		TESGlobal* chanceVar; // 10
	};
	static_assert(sizeof(WeatherEntry) == 0x18);
}
