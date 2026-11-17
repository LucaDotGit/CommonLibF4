#pragma once

#include "RE/N/NiColorA.hpp"
#include "RE/N/NiRect.hpp"

namespace RE
{
	class UIShaderColors
	{
	public:
		enum class Flags : std::uint32_t
		{
			None = 0,
			BackgroundQuad = 1 << 0,
			ColorMultiplier = 1 << 1,
			VerticalGradient = 1 << 2,
			UseAlphaForDropshadow = 1 << 3
		};

		// members
		NiRectF backgroundQuad;							  // 0x00
		NiColorA backgroundColor;						  // 0x10
		NiColorA colorMultipliers;						  // 0x20
		REX::Float32 colorBrightness;					  // 0x30
		REX::EnumSet<Flags, std::uint32_t> enabledStates; // 0x34
	};

	static_assert(sizeof(UIShaderColors) == 0x38);
}
