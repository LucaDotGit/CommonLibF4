#pragma once

#include "RE/T/TESForm.hpp"
#include "RE/T/TESModel.hpp"
#include "RE/T/TESTexture.hpp"
#include "RE/T/TESWeatherList.hpp"
#include "RE/T/Timing.hpp"

namespace RE
{
	class __declspec(novtable) TESClimate
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESClimate };
		inline static constexpr auto VTABLE{ VTABLE::TESClimate };
		inline static constexpr auto FORM_TYPE{ FormType::kClimate };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class MiscData : std::int32_t
		{
			kVolatility = 4,
			kMoonData = 5,
			kNumSliders = 6
		};

		enum class SkyObject : std::int32_t
		{
			kSun = 0,
			kSunGlare = 1,

			kTotal = 2
		};

		enum class TextureType : std::int32_t
		{
			kSun = 0,
			kGlare = 1,

			kTotal = 2
		};

		enum class TransTime : std::int32_t
		{
			kSunriseBegin = 0,
			kSunriseEnd = 1,
			kSunsetBegin = 2,
			kSunsetEnd = 3,

			kTotal = 4
		};

		void SetWeatherEntries(std::span<std::unique_ptr<WeatherEntry>> a_entries);
		void ClearWeatherEntries();

		// members
		TESModel nightSky;														  // 20
		TESWeatherList weatherList;												  // 50
		std::array<TESTexture, std::to_underlying(SkyObject::kTotal)> skyObjects; // 60
		Timing timing;															  // 80
	};
	static_assert(sizeof(TESClimate) == 0x88);
}
