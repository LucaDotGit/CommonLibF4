#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/H/hkVector4.hpp"

namespace RE
{
	class TrapData
	{
	public:
		// members
		ObjectRefHandle trap;		// 00
		REX::Float32 damage;		// 04
		REX::Float32 leveledDamage; // 08
		REX::Float32 minVelocity;	// 0C
		REX::Float32 pushBack;		// 10
		REX::Float32 deathPushback; // 14
		REX::Float32 stagger;		// 18
		bool continuous;			// 1C
		hkVector4 pushbackVector;	// 20
		hkVector4 hitLocation;		// 30
		std::uint32_t material;		// 40
	};
	static_assert(sizeof(TrapData) == 0x50);
}
