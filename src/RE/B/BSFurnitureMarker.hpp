#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BSFurnitureMarker
	{
	public:
		// members
		NiPoint3 position;				  // 0x00
		BGSKeyword* actorMustHaveKeyword; // 0x10
		REX::Float32 heading;			  // 0x18
		std::uint32_t allowedAnimations;  // 0x1C
	};

	static_assert(sizeof(BSFurnitureMarker) == 0x20);
}
