#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BGSModelMaterialSwap;

	class DestructibleObjectStage
	{
	public:
		GAME_HEAP_REDEFINE_NEW(DestructibleObjectStage);

		// members
		std::int8_t modelDamageStage;			// 0x00
		std::int8_t healthPercentage;			// 0x01
		std::int8_t flags;						// 0x02
		std::uint32_t selfDamagePerSecond;		// 0x04
		BGSExplosion* explosion;				// 0x08
		BGSDebris* debris;						// 0x10
		std::uint32_t debrisCount;				// 0x18
		BGSModelMaterialSwap* replacementModel; // 0x20
		BSFixedString sequenceName;				// 0x28
	};

	static_assert(sizeof(DestructibleObjectStage) == 0x30);
}
