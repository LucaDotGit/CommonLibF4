#include "RE/T/TESClimate.hpp"

#include "RE/W/WeatherEntry.hpp"

namespace RE
{
	void TESClimate::SetWeatherEntries(std::span<std::unique_ptr<WeatherEntry>> a_entries)
	{
		ClearWeatherEntries();

		for (auto& entry : a_entries) {
			if (!entry) {
				continue;
			}

			weatherList.push_back(entry.release());
		}
	}

	void TESClimate::ClearWeatherEntries()
	{
		for (auto*& element : weatherList) {
			if (!element) {
				continue;
			}

			delete element;
			element = nullptr;
		}

		weatherList.clear();
	}
}
