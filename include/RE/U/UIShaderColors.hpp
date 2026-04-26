#pragma once

#include "RE/N/NiColor.hpp"
#include "RE/N/NiRect.hpp"

namespace RE
{
	class UIShaderColors
	{
	public:
		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kBackgroundQuad = 1 << 0,
			kColorMultiplier = 1 << 1,
			kVerticalGradient = 1 << 2,
			kUseAlphaForDropshadow = 1 << 3
		};

		// members
		NiRect<REX::Float32> backgroundQuad;			  // 00
		NiColorA backgroundColor;						  // 10
		NiColorA colorMultipliers;						  // 20
		REX::Float32 colorBrightness;					  // 30
		REX::EnumSet<Flags, std::uint32_t> enabledStates; // 34
	};
	static_assert(sizeof(UIShaderColors) == 0x38);
}
