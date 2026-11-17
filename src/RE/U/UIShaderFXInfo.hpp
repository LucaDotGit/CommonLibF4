#pragma once

#include "RE/U/UIShaderColors.hpp"

namespace RE
{
	class UIShaderFXInfo
	{
	public:
		// members
		alignas(0x10) NiRectF renderQuad; // 0x00
		UIShaderColors shaderFX;		  // 0x10
	};

	static_assert(sizeof(UIShaderFXInfo) == 0x50);
}
