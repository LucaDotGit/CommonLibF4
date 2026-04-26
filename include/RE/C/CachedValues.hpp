#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/C/CachedValueData.hpp"

namespace RE
{
	class CachedValues
	{
	public:
		// members
		REX::Float32 cachedRadius;							// 00
		REX::Float32 cachedWidth;							// 04
		REX::Float32 cachedLength;							// 08
		REX::Float32 cachedForwardLength;					// 0C
		REX::Float32 cachedDPS;								// 10
		REX::Float32 cachedEyeLevel;						// 14
		REX::Float32 cachedWalkSpeed;						// 18
		REX::Float32 cachedRunSpeed;						// 1C
		REX::Float32 cachedJogSpeed;						// 20
		REX::Float32 cachedFastWalkSpeed;					// 24
		std::uint32_t booleanValues;						// 28
		std::uint32_t flags;								// 2C
		BSTArray<CachedValueData> actorValueCache;			// 30
		BSTArray<CachedValueData> permanentActorValueCache; // 48
	};
	static_assert(sizeof(CachedValues) == 0x60);
}
