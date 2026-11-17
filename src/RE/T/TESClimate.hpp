#pragma once

#include "RE/T/TESForm.hpp"
#include "RE/T/TESModel.hpp"
#include "RE/T/TESTexture.hpp"
#include "RE/T/TESWeatherList.hpp"
#include "RE/T/Timing.hpp"

namespace RE
{
	class __declspec(novtable) TESClimate : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESClimate;
		inline static constexpr const auto& VTABLE = VTABLE::TESClimate;
		inline static constexpr auto FORM_TYPE = FormType::Climate;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class MiscData : std::int32_t
		{
			Volatility = 4,
			MoonData = 5,
			NumSliders = 6
		};

		enum class SkyObject : std::int32_t
		{
			Sun = 0,
			SunGlare = 1,

			_Count = 2
		};

		enum class TextureType : std::int32_t
		{
			Sun = 0,
			Glare = 1,

			_Count = 2
		};

		enum class TransTime : std::int32_t
		{
			SunriseBegin = 0,
			SunriseEnd = 1,
			SunsetBegin = 2,
			SunsetEnd = 3,

			_Count = 4
		};

		void SetWeatherEntries(std::span<std::unique_ptr<WeatherEntry>> a_entries);
		void ClearWeatherEntries();

		// members
		TESModel nightSky;														  // 0x20
		TESWeatherList weatherList;												  // 0x50
		std::array<TESTexture, std::to_underlying(SkyObject::_Count)> skyObjects; // 0x60
		Timing timing;															  // 0x80
	};

	static_assert(sizeof(TESClimate) == 0x88);
}
