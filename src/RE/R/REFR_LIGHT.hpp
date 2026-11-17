#pragma once

#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSLight;
	class NiLight;

	class REFR_LIGHT
	{
	public:
		GAME_HEAP_REDEFINE_NEW(REFR_LIGHT);

		// members
		NiPointer<NiLight> light;	// 0x00
		NiPointer<BSLight> BSLight; // 0x08
		REX::Float32 wantDimmer;	// 0x10
	};

	static_assert(sizeof(REFR_LIGHT) == 0x18);
}
