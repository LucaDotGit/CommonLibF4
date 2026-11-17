#pragma once

#include "RE/B/BGSDirectionalAmbientLightingColors.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESModel.hpp"
#include "RE/T/TESTexture1024.hpp"

namespace RE
{
	class BGSReferenceEffect;
	class BGSShaderParticleGeometryData;

	class __declspec(novtable) TESWeather : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESWeather;
		inline static constexpr const auto& VTABLE = VTABLE::TESWeather;
		inline static constexpr auto FORM_TYPE = FormType::Weather;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class ColorTime : std::int32_t
		{
			Sunrise = 0,
			Day = 1,
			Sunset = 2,
			Night = 3,
			EarlySunrise = 4,
			LateSunrise = 5,
			EarlySunset = 6,
			LateSunset = 7,

			_Count = 8
		};

		enum class SpellContext : std::int32_t
		{
			ApplyOnLightning = 0,
			ApplyWhenActive = 1
		};

		enum class SoundType : std::int32_t
		{
			Default = 0,
			Precipitation = 1,
			Wind = 2,
			Thunder = 3,

			_Count = 4
		};

		enum class WeatherData : std::int32_t
		{
			WindSpeed = 0,
			CloudSpeedY = 1,
			CloudSpeedX = 2,
			TransDelta = 3,
			SunGlare = 4,
			SunDamage = 5,
			BeginPrecip = 6,
			EndPrecip = 7,
			BeginThunder = 8,
			EndThunder = 9,
			ThunderFreq = 10,
			Flags = 11,
			LightningR = 12,
			LightningG = 13,
			LightningB = 14,
			BeginEffect = 15,
			EndEffect = 16,
			WindDir = 17,
			WindDirRange = 18,
			WindTurbulence = 19,

			_Count = 20
		};

		enum class WeatherDataFlags : std::uint32_t
		{
			None = 0,
			Pleasant = 1 << 0,
			Cloudy = 1 << 1,
			Rainy = 1 << 2,
			Snow = 1 << 3,
			PermAurora = 1 << 4,
			AuroraFollowsSun = 1 << 5,
			RainOcclusion = 1 << 6,
			HudRain = 1 << 7
		};

		class SpellData
		{
		public:
			// members
			MagicItem* spell;		// 0x00
			REX::Float32 threshold; // 0x08
		};

		static_assert(sizeof(SpellData) == 0x10);

		class WeatherSound
		{
		public:
			// members
			BGSSoundDescriptorForm* soundForm;		 // 0x00
			REX::Enum<SoundType, std::int32_t> type; // 0x08
		};

		static_assert(sizeof(WeatherSound) == 0x10);

		class WeatherSoundList : public BSSimpleList<WeatherSound*>
		{
		public:
		};

		static_assert(sizeof(WeatherSoundList) == 0x10);

		// members
		REX::Enum<SpellContext, std::int32_t> context;										 // 0x020
		std::array<TESTexture1024, 32> cloudTexture;										 // 0x028
		std::array<std::int8_t, 32> cloudLayerSpeedY;										 // 0x228
		std::array<std::int8_t, 32> cloudLayerSpeedX;										 // 0x248
		std::array<std::array<std::uint32_t, 32>, 8> cloudColorData;						 // 0x268
		std::array<std::array<REX::Float32, 32>, 8> cloudAlpha;								 // 0x668
		std::uint32_t cloudLayerDisabledBits;												 // 0xA68
		std::array<std::int8_t, std::to_underlying(WeatherData::_Count)> weatherData;		 // 0xA6C
		std::array<REX::Float32, 18> fogData;												 // 0xA80
		std::array<std::array<std::uint32_t, 19>, 8> colorData;								 // 0xAC8
		std::array<std::array<REX::Float32, 4>, 8> fogColorScales;							 // 0xD28
		std::array<SpellData, 2> weatherSpellData;											 // 0xDA8
		WeatherSoundList soundList;															 // 0xDC8
		BSTArray<TESObjectSTAT*> skyStatics;												 // 0xDD8
		std::uint32_t numCloudLayers;														 // 0xDF0
		std::array<TESImageSpace*, 8> imageSpace;											 // 0xDF8
		std::array<BGSGodRays*, 8> godRays;													 // 0xE38
		std::array<BGSDirectionalAmbientLightingColors, 8> directionalAmbientLightingColors; // 0xE78
		TESModel aurora;																	 // 0xF78
		BGSLensFlare* sunGlareLensFlare;													 // 0xFA8
		REX::Float32 volatilityMult;														 // 0xFB0
		REX::Float32 visibilityMult;														 // 0xFB4
		BGSShaderParticleGeometryData* precipitationData;									 // 0xFB8
		BGSReferenceEffect* referenceEffect;												 // 0xFC0
	};

	static_assert(sizeof(TESWeather) == 0xFC8);
}
