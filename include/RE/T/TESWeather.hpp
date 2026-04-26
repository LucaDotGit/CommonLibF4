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

	class __declspec(novtable) TESWeather
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESWeather };
		inline static constexpr auto VTABLE{ VTABLE::TESWeather };
		inline static constexpr auto FORM_TYPE{ FormType::kWeather };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class ColorTime : std::int32_t
		{
			kSunrise = 0,
			kDay = 1,
			kSunset = 2,
			kNight = 3,
			kEarlySunrise = 4,
			kLateSunrise = 5,
			kEarlySunset = 6,
			kLateSunset = 7,

			kTotal = 8
		};

		enum class SpellContext : std::int32_t
		{
			kApplyOnLightning = 0,
			kApplyWhenActive = 1
		};

		enum class SoundType : std::int32_t
		{
			kDefault = 0,
			kPrecipitation = 1,
			kWind = 2,
			kThunder = 3,

			kTotal = 4
		};

		enum class WeatherData : std::int32_t
		{
			kWindSpeed = 0,
			kCloudSpeedY = 1,
			kCloudSpeedX = 2,
			kTransDelta = 3,
			kSunGlare = 4,
			kSunDamage = 5,
			kBeginPrecip = 6,
			kEndPrecip = 7,
			kBeginThunder = 8,
			kEndThunder = 9,
			kThunderFreq = 10,
			kFlags = 11,
			kLightningR = 12,
			kLightningG = 13,
			kLightningB = 14,
			kBeginEffect = 15,
			kEndEffect = 16,
			kWindDir = 17,
			kWindDirRange = 18,
			kWindTurbulence = 19,

			kTotal = 20
		};

		enum class WeatherDataFlags : std::uint32_t
		{
			kNone = 0,
			kPleasant = 1 << 0,
			kCloudy = 1 << 1,
			kRainy = 1 << 2,
			kSnow = 1 << 3,
			kPermAurora = 1 << 4,
			kAuroraFollowsSun = 1 << 5,
			kRainOcclusion = 1 << 6,
			kHudRain = 1 << 7
		};

		class SpellData
		{
		public:
			// members
			MagicItem* spell;		// 00
			REX::Float32 threshold; // 08
		};
		static_assert(sizeof(SpellData) == 0x10);

		class WeatherSound
		{
		public:
			// members
			BGSSoundDescriptorForm* soundForm;		 // 00
			REX::Enum<SoundType, std::int32_t> type; // 08
		};
		static_assert(sizeof(WeatherSound) == 0x10);

		class WeatherSoundList
			: public BSSimpleList<WeatherSound*>
		{
		public:
		};
		static_assert(sizeof(WeatherSoundList) == 0x10);

		// members
		REX::Enum<SpellContext, std::int32_t> context;										 // 020
		std::array<TESTexture1024, 32> cloudTexture;										 // 028
		std::array<std::int8_t, 32> cloudLayerSpeedY;										 // 228
		std::array<std::int8_t, 32> cloudLayerSpeedX;										 // 248
		std::array<std::array<std::uint32_t, 32>, 8> cloudColorData;						 // 268
		std::array<std::array<REX::Float32, 32>, 8> cloudAlpha;								 // 668
		std::uint32_t cloudLayerDisabledBits;												 // A68
		std::array<std::int8_t, std::to_underlying(WeatherData::kTotal)> weatherData;		 // A6C
		std::array<REX::Float32, 18> fogData;												 // A80
		std::array<std::array<std::uint32_t, 19>, 8> colorData;								 // AC8
		std::array<std::array<REX::Float32, 4>, 8> fogColorScales;							 // D28
		std::array<SpellData, 2> weatherSpellData;											 // DA8
		WeatherSoundList soundList;															 // DC8
		BSTArray<TESObjectSTAT*> skyStatics;												 // DD8
		std::uint32_t numCloudLayers;														 // DF0
		std::array<TESImageSpace*, 8> imageSpace;											 // DF8
		std::array<BGSGodRays*, 8> godRays;													 // E38
		std::array<BGSDirectionalAmbientLightingColors, 8> directionalAmbientLightingColors; // E78
		TESModel aurora;																	 // F78
		BGSLensFlare* sunGlareLensFlare;													 // FA8
		REX::Float32 volatilityMult;														 // FB0
		REX::Float32 visibilityMult;														 // FB4
		BGSShaderParticleGeometryData* precipitationData;									 // FB8
		BGSReferenceEffect* referenceEffect;												 // FC0
	};
	static_assert(sizeof(TESWeather) == 0xFC8);
}
