#pragma once

#include "RE/U/UIShaderColors.hpp"

namespace RE
{
	class UIShaderFXInfo
	{
	public:
		// members
		alignas(0x10) NiRect<REX::Float32> renderQuad; // 00
		UIShaderColors shaderFX;					   // 10
	};
	static_assert(sizeof(UIShaderFXInfo) == 0x50);
}
