#pragma once

#include "RE/B/BGSDirectionalAmbientLightingColors.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class INTERIOR_DATA
	{
	public:
		inline static constexpr auto DIRECTIONAL_X_SHIFT = 16;
		inline static constexpr auto DIRECTIONAL_Y_MASK = std::numeric_limits<std::uint16_t>::max();

		GAME_HEAP_REDEFINE_NEW(INTERIOR_DATA);

		[[nodiscard]] std::uint16_t GetDirectionalX() const noexcept { return static_cast<std::uint16_t>(directionalXY >> DIRECTIONAL_X_SHIFT); }
		[[nodiscard]] std::uint16_t GetDirectionalY() const noexcept { return static_cast<std::uint16_t>(directionalXY & DIRECTIONAL_Y_MASK); }

		// members
		std::uint32_t ambient;												  // 00
		std::uint32_t directional;											  // 04
		std::uint32_t fogColorNear;											  // 08
		REX::Float32 fogNear;												  // 0C
		REX::Float32 fogFar;												  // 10
		std::uint32_t directionalXY;										  // 14
		std::uint32_t directionalZ;											  // 18
		REX::Float32 directionalFade;										  // 1C
		REX::Float32 clipDist;												  // 20
		REX::Float32 fogPower;												  // 24
		BGSDirectionalAmbientLightingColors directionalAmbientLightingColors; // 28
		std::uint32_t fogColorFar;											  // 48
		REX::Float32 fogClamp;												  // 4C
		REX::Float32 lightFadeStart;										  // 50
		REX::Float32 lightFadeEnd;											  // 54
		std::uint32_t lightingTemplateInheritanceFlags;						  // 58
		REX::Float32 fogHeightMid;											  // 5C
		REX::Float32 fogHeightRange;										  // 60
		std::uint32_t fogColorHighNear;										  // 64
		std::uint32_t fogColorHighFar;										  // 68
		REX::Float32 fogHighDensityScale;									  // 6C
		REX::Float32 fogNearColorScale;										  // 70
		REX::Float32 fogFarColorScale;										  // 74
		REX::Float32 fogHighNearColorScale;									  // 78
		REX::Float32 fogHighFarColorScale;									  // 7C
		REX::Float32 fogFarHeightMid;										  // 80
		REX::Float32 fogFarHeightRange;										  // 84
		std::uint32_t interiorOffset;										  // 88
	};
	static_assert(sizeof(INTERIOR_DATA) == 0x8C);
}
