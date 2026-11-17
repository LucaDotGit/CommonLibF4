#pragma once

#include "RE/B/BGSDirectionalAmbientLightingColors.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class INTERIOR_DATA
	{
	public:
		inline static constexpr auto DIRECTIONAL_X_SHIFT = static_cast<std::uint16_t>(16);
		inline static constexpr auto DIRECTIONAL_Y_MASK = std::numeric_limits<std::uint16_t>::max();

		GAME_HEAP_REDEFINE_NEW(INTERIOR_DATA);

		[[nodiscard]]
		auto GetDirectionalX() const noexcept -> std::uint16_t
		{
			return static_cast<std::uint16_t>(directionalXY >> DIRECTIONAL_X_SHIFT);
		}

		[[nodiscard]]
		auto GetDirectionalY() const noexcept -> std::uint16_t
		{
			return static_cast<std::uint16_t>(directionalXY & DIRECTIONAL_Y_MASK);
		}

		// members
		std::uint32_t ambient;												  // 0x00
		std::uint32_t directional;											  // 0x04
		std::uint32_t fogColorNear;											  // 0x08
		REX::Float32 fogNear;												  // 0x0C
		REX::Float32 fogFar;												  // 0x10
		std::uint32_t directionalXY;										  // 0x14
		std::uint32_t directionalZ;											  // 0x18
		REX::Float32 directionalFade;										  // 0x1C
		REX::Float32 clipDist;												  // 0x20
		REX::Float32 fogPower;												  // 0x24
		BGSDirectionalAmbientLightingColors directionalAmbientLightingColors; // 0x28
		std::uint32_t fogColorFar;											  // 0x48
		REX::Float32 fogClamp;												  // 0x4C
		REX::Float32 lightFadeStart;										  // 0x50
		REX::Float32 lightFadeEnd;											  // 0x54
		std::uint32_t lightingTemplateInheritanceFlags;						  // 0x58
		REX::Float32 fogHeightMid;											  // 0x5C
		REX::Float32 fogHeightRange;										  // 0x60
		std::uint32_t fogColorHighNear;										  // 0x64
		std::uint32_t fogColorHighFar;										  // 0x68
		REX::Float32 fogHighDensityScale;									  // 0x6C
		REX::Float32 fogNearColorScale;										  // 0x70
		REX::Float32 fogFarColorScale;										  // 0x74
		REX::Float32 fogHighNearColorScale;									  // 0x78
		REX::Float32 fogHighFarColorScale;									  // 0x7C
		REX::Float32 fogFarHeightMid;										  // 0x80
		REX::Float32 fogFarHeightRange;										  // 0x84
		std::uint32_t interiorOffset;										  // 0x88
	};

	static_assert(sizeof(INTERIOR_DATA) == 0x8C);
}
