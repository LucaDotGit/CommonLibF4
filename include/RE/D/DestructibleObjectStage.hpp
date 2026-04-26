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
		std::int8_t modelDamageStage;			// 00
		std::int8_t healthPercentage;			// 01
		std::int8_t flags;						// 02
		std::uint32_t selfDamagePerSecond;		// 04
		BGSExplosion* explosion;				// 08
		BGSDebris* debris;						// 10
		std::uint32_t debrisCount;				// 18
		BGSModelMaterialSwap* replacementModel; // 20
		BSFixedString sequenceName;				// 28
	};
	static_assert(sizeof(DestructibleObjectStage) == 0x30);
}
