#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/S/SkyEffectController.hpp"

namespace RE
{
	class Atmosphere;
	class BSMultiBoundNode;
	class Clouds;
	class ImageSpaceModifierInstanceForm;
	class Moon;
	class NiNode;
	class NiTexture;
	class Precipitation;
	class ReferenceEffect;
	class SkySound;
	class Stars;
	class Sun;

	class __declspec(novtable) Sky
	{
	public:
		inline static constexpr auto RTTI{ RTTI::Sky };
		inline static constexpr auto VTABLE{ VTABLE::Sky };

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kFastTravel = 1 << 4,
			kHideSky = 1 << 7,
			kUpdateSunriseBegin = 1 << 9,
			kUpdateSunriseEnd = 1 << 10,
			kUpdateSunsetBegin = 1 << 11,
			kUpdateSunsetEnd = 1 << 12,
			kUpdateColorsSunriseBegin = 1 << 13,
			kUpdateColorsSunsetEnd = 1 << 14,
			kUpdateWind = 1 << 20,
			kReleaseWeatherOverride = 1 << 21
		};

		enum class FogDistance : std::int32_t
		{
			kNear = 0,
			kFar = 1,
			kWaterNear = 2,
			kWaterFar = 3,
			kHeightMid = 4,
			kHeightRange = 5,
			kFarHeightMid = 6,
			kFarHeightRange = 7,

			kTotal = 8
		};

		enum class Mode : std::int32_t
		{
			kNone = 0,
			kInterior = 1,
			kSkyDomeOnly = 2,
			kFull = 3,

			kTotal = 4
		};

		enum class WeatherStateOperation : std::int32_t
		{
			kSave = 0,
			kRestore = 1,
			kClear = 2
		};

		class SkyStaticRefData
		{
		public:
			// members
			BSTPair<ObjectRefHandle, std::uint8_t> data; // 00
		};
		static_assert(sizeof(SkyStaticRefData) == 0x08);

		virtual ~Sky(); // 00

		[[nodiscard]] static Sky* GetSingleton()
		{
			using FuncType = decltype(&Sky::GetSingleton);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Sky::Singleton };
			return std::invoke(FUNC);
		}

		void ForceWeather(TESWeather* a_weather, bool a_override)
		{
			using FuncType = decltype(&Sky::ForceWeather);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Sky::ForceWeather };
			FUNC(this, a_weather, a_override);
		}

		void ReleaseWeatherOverride()
		{
			if (overrideWeather) {
				flags.set(Flags::kReleaseWeatherOverride);
				overrideWeather = nullptr;
			}
		}

		void ResetWeather()
		{
			using FuncType = decltype(&Sky::ResetWeather);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Sky::ResetWeather };
			FUNC(this);
		}

		// members
		NiPointer<BSMultiBoundNode> root;												// 008
		NiPointer<NiNode> moonsRoot;													// 010
		NiPointer<NiNode> auroraRoot;													// 018
		void* aurora3D;																	// 020 - TODO: `BSModelDB::Handle`
		BGSLightingTemplate* extLightingOverride;										// 028
		ObjectRefHandle currentRoom;													// 030
		ObjectRefHandle previousRoom;													// 034
		REX::Float32 lightingTransition;												// 038
		REX::Float32 lightingTransitionTimer;											// 03C
		TESClimate* currentClimate;														// 040
		TESWeather* currentWeather;														// 048
		TESWeather* lastWeather;														// 050
		TESWeather* defaultWeather;														// 058
		TESWeather* overrideWeather;													// 060
		TESRegion* currentRegion;														// 068
		Atmosphere* atmosphere;															// 070
		Stars* stars;																	// 078
		Sun* sun;																		// 080
		Clouds* clouds;																	// 088
		Moon* masser;																	// 090
		Moon* secunda;																	// 098
		Precipitation* precip;															// 0A0
		std::array<NiColor, 19> skyColors;												// 0A8
		std::array<NiColor, 19> prevSkyColors;											// 18C
		std::array<std::array<NiColor, 3>, 2> prevDirAmbColors;							// 270
		NiColorA prevSpecTintFres;														// 2B8
		TESImageSpace* prevImageSpace;													// 2C8
		std::array<REX::Float32, 8> prevFogDistances;									// 2D0
		REX::Float32 prevFogHeight;														// 2F0
		REX::Float32 prevFogPower;														// 2F4
		REX::Float32 prevFogClamp;														// 2F8
		REX::Float32 prevFogHighDensityScale;											// 2FC
		REX::Float32 lastExtWetness;													// 300
		NiColor waterFogColor;															// 304
		NiColor sunSpecularColor;														// 310
		REX::Float32 windSpeed;															// 31C
		REX::Float32 windAngle;															// 320
		REX::Float32 windTurbulence;													// 324
		std::array<REX::Float32, std::to_underlying(FogDistance::kTotal)> fogDistances; // 328
		REX::Float32 fogHeight;															// 348
		REX::Float32 fogPower;															// 34C
		REX::Float32 fogClamp;															// 350
		REX::Float32 fogHighDensityScale;												// 354
		REX::Float32 currentGameHour;													// 358
		REX::Float32 lastWeatherUpdate;													// 35C
		REX::Float32 currentWeatherPct;													// 360
		REX::Float32 lastWindDirection;													// 364
		REX::Float32 lastWindDirectionRange;											// 368
		REX::Enum<Mode, std::int32_t> mode;												// 36C
		BSSimpleList<SkySound*>* skySoundList;											// 370
		REX::Float32 flash;																// 378
		std::uint64_t flashTime;														// 380
		std::uint32_t lastMoonPhaseUpdate;												// 388
		REX::Float32 windowReflectionTimer;												// 38C
		REX::Float32 accelBeginPct;														// 390
		REX::EnumSet<Flags, std::uint32_t> flags;										// 394
		ImageSpaceModifierInstanceForm* currentWeatherImageSpaceMod01;					// 398
		ImageSpaceModifierInstanceForm* currentWeatherImageSpaceMod02;					// 3A0
		ImageSpaceModifierInstanceForm* lastWeatherImageSpaceMod01;						// 3A8
		ImageSpaceModifierInstanceForm* lastWeatherImageSpaceMod02;						// 3B0
		std::array<std::array<NiColor, 3>, 2> directionalAmbientColors;					// 3B8
		NiColor ambientSpecularTint;													// 400
		REX::Float32 ambientSpecularFresnel;											// 40C
		REX::Float32 auroraInStart;														// 410
		REX::Float32 auroraIn;															// 414
		REX::Float32 auroraOutStart;													// 418
		REX::Float32 auroraOut;															// 41C
		NiPointer<ReferenceEffect> currentReferenceEffect;								// 420
		NiPointer<ReferenceEffect> lastReferenceEffect;									// 428
		SkyEffectController effectController;											// 430
		BSTArray<NiPointer<NiTexture>> storedCloudTextures;								// 438
		BSTArray<NiPointer<NiTexture>> storedWorldMapCloudTextures;						// 450
		BSTArray<SkyStaticRefData> skyStaticRefDataArray;								// 468
	};
	static_assert(sizeof(Sky) == 0x480);
}
