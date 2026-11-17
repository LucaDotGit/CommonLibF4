#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/C/CachedValueData.hpp"

namespace RE
{
	class CachedValues
	{
	public:
		// members
		REX::Float32 cachedRadius;							// 0x00
		REX::Float32 cachedWidth;							// 0x04
		REX::Float32 cachedLength;							// 0x08
		REX::Float32 cachedForwardLength;					// 0x0C
		REX::Float32 cachedDPS;								// 0x10
		REX::Float32 cachedEyeLevel;						// 0x14
		REX::Float32 cachedWalkSpeed;						// 0x18
		REX::Float32 cachedRunSpeed;						// 0x1C
		REX::Float32 cachedJogSpeed;						// 0x20
		REX::Float32 cachedFastWalkSpeed;					// 0x24
		std::uint32_t booleanValues;						// 0x28
		std::uint32_t flags;								// 0x2C
		BSTArray<CachedValueData> actorValueCache;			// 0x30
		BSTArray<CachedValueData> permanentActorValueCache; // 0x48
	};

	static_assert(sizeof(CachedValues) == 0x60);
}
