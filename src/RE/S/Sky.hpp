#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/N/NiColorA.hpp"
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
		inline static constexpr const auto& RTTI = RTTI::Sky;
		inline static constexpr const auto& VTABLE = VTABLE::Sky;

		enum class Flags : std::uint32_t
		{
			None = 0,
			FastTravel = 1 << 4,
			HideSky = 1 << 7,
			UpdateSunriseBegin = 1 << 9,
			UpdateSunriseEnd = 1 << 10,
			UpdateSunsetBegin = 1 << 11,
			UpdateSunsetEnd = 1 << 12,
			UpdateColorsSunriseBegin = 1 << 13,
			UpdateColorsSunsetEnd = 1 << 14,
			UpdateWind = 1 << 20,
			ReleaseWeatherOverride = 1 << 21
		};

		enum class FogDistance : std::int32_t
		{
			Near = 0,
			Far = 1,
			WaterNear = 2,
			WaterFar = 3,
			HeightMid = 4,
			HeightRange = 5,
			FarHeightMid = 6,
			FarHeightRange = 7,

			_Count = 8
		};

		enum class Mode : std::int32_t
		{
			None = 0,
			Interior = 1,
			SkyDomeOnly = 2,
			Full = 3,

			_Count = 4
		};

		enum class WeatherStateOperation : std::int32_t
		{
			Save = 0,
			Restore = 1,
			Clear = 2
		};

		class SkyStaticRefData
		{
		public:
			// members
			BSTPair<ObjectRefHandle, std::uint8_t> data; // 0x00
		};

		static_assert(sizeof(SkyStaticRefData) == 0x08);

		virtual ~Sky(); // 0x00

		[[nodiscard]]
		static auto GetSingleton() -> Sky*
		{
			using FuncType = decltype(&Sky::GetSingleton);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Sky::Singleton);
			return std::invoke(FUNC);
		}

		void ForceWeather(TESWeather* a_weather, bool a_override)
		{
			using FuncType = decltype(&Sky::ForceWeather);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Sky::ForceWeather);
			std::invoke(FUNC, this, a_weather, a_override);
		}

		void ReleaseWeatherOverride()
		{
			if (overrideWeather) {
				flags.set(Flags::ReleaseWeatherOverride);
				overrideWeather = nullptr;
			}
		}

		void ResetWeather()
		{
			using FuncType = decltype(&Sky::ResetWeather);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Sky::ResetWeather);
			std::invoke(FUNC, this);
		}

		// members
		NiPointer<BSMultiBoundNode> root;						// 0x008
		NiPointer<NiNode> moonsRoot;							// 0x010
		NiPointer<NiNode> auroraRoot;							// 0x018
		void* aurora3D;											// 0x020 - To-Do: `BSModelDB::Handle`
		BGSLightingTemplate* extLightingOverride;				// 0x028
		ObjectRefHandle currentRoom;							// 0x030
		ObjectRefHandle previousRoom;							// 0x034
		REX::Float32 lightingTransition;						// 0x038
		REX::Float32 lightingTransitionTimer;					// 0x03C
		TESClimate* currentClimate;								// 0x040
		TESWeather* currentWeather;								// 0x048
		TESWeather* lastWeather;								// 0x050
		TESWeather* defaultWeather;								// 0x058
		TESWeather* overrideWeather;							// 0x060
		TESRegion* currentRegion;								// 0x068
		Atmosphere* atmosphere;									// 0x070
		Stars* stars;											// 0x078
		Sun* sun;												// 0x080
		Clouds* clouds;											// 0x088
		Moon* masser;											// 0x090
		Moon* secunda;											// 0x098
		Precipitation* precip;									// 0x0A0
		std::array<NiColor, 19> skyColors;						// 0x0A8
		std::array<NiColor, 19> prevSkyColors;					// 0x18C
		std::array<std::array<NiColor, 3>, 2> prevDirAmbColors; // 0x270
		NiColorA prevSpecTintFres;								// 0x2B8
		TESImageSpace* prevImageSpace;							// 0x2C8
		std::array<REX::Float32, 8> prevFogDistances;			// 0x2D0
		REX::Float32 prevFogHeight;								// 0x2F0
		REX::Float32 prevFogPower;								// 0x2F4
		REX::Float32 prevFogClamp;								// 0x2F8
		REX::Float32 prevFogHighDensityScale;					// 0x2FC
		REX::Float32 lastExtWetness;							// 0x300
		NiColor waterFogColor;									// 0x304
		NiColor sunSpecularColor;								// 0x310
		REX::Float32 windSpeed;									// 0x31C
		REX::Float32 windAngle;									// 0x320
		REX::Float32 windTurbulence;							// 0x324
		std::array<REX::Float32, std::to_underlying(FogDistance::_Count)> fogDistances; // 0x328
		REX::Float32 fogHeight;															// 0x348
		REX::Float32 fogPower;															// 0x34C
		REX::Float32 fogClamp;															// 0x350
		REX::Float32 fogHighDensityScale;												// 0x354
		REX::Float32 currentGameHour;													// 0x358
		REX::Float32 lastWeatherUpdate;													// 0x35C
		REX::Float32 currentWeatherPct;													// 0x360
		REX::Float32 lastWindDirection;													// 0x364
		REX::Float32 lastWindDirectionRange;											// 0x368
		REX::Enum<Mode, std::int32_t> mode;												// 0x36C
		BSSimpleList<SkySound*>* skySoundList;											// 0x370
		REX::Float32 flash;																// 0x378
		std::uint64_t flashTime;														// 0x380
		std::uint32_t lastMoonPhaseUpdate;												// 0x388
		REX::Float32 windowReflectionTimer;												// 0x38C
		REX::Float32 accelBeginPct;														// 0x390
		REX::EnumSet<Flags, std::uint32_t> flags;										// 0x394
		ImageSpaceModifierInstanceForm* currentWeatherImageSpaceMod01;					// 0x398
		ImageSpaceModifierInstanceForm* currentWeatherImageSpaceMod02;					// 0x3A0
		ImageSpaceModifierInstanceForm* lastWeatherImageSpaceMod01;						// 0x3A8
		ImageSpaceModifierInstanceForm* lastWeatherImageSpaceMod02;						// 0x3B0
		std::array<std::array<NiColor, 3>, 2> directionalAmbientColors;					// 0x3B8
		NiColor ambientSpecularTint;													// 0x400
		REX::Float32 ambientSpecularFresnel;											// 0x40C
		REX::Float32 auroraInStart;														// 0x410
		REX::Float32 auroraIn;															// 0x414
		REX::Float32 auroraOutStart;													// 0x418
		REX::Float32 auroraOut;															// 0x41C
		NiPointer<ReferenceEffect> currentReferenceEffect;								// 0x420
		NiPointer<ReferenceEffect> lastReferenceEffect;									// 0x428
		SkyEffectController effectController;											// 0x430
		BSTArray<NiPointer<NiTexture>> storedCloudTextures;								// 0x438
		BSTArray<NiPointer<NiTexture>> storedWorldMapCloudTextures;						// 0x450
		BSTArray<SkyStaticRefData> skyStaticRefDataArray;								// 0x468
	};

	static_assert(sizeof(Sky) == 0x480);
}
