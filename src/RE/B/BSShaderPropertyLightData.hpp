#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class BSLight;

	class BSShaderPropertyLightData
	{
	public:
		// members
		std::uint32_t lightListFence;	// 0x00
		std::uint32_t shadowAccumFlags; // 0x04
		std::uint32_t lightListChanged; // 0x08
		BSTArray<BSLight*> lightList;	// 0x10
	};

	static_assert(sizeof(BSShaderPropertyLightData) == 0x28);
}
