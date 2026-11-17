#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class WeatherEntry
	{
	public:
		GAME_HEAP_REDEFINE_NEW(WeatherEntry);

		// members
		TESWeather* weather;  // 0x00
		std::uint32_t chance; // 0x08
		TESGlobal* chanceVar; // 0x10
	};

	static_assert(sizeof(WeatherEntry) == 0x18);
}
