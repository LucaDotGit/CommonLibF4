#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/H/hkVector4.hpp"

namespace RE
{
	class TrapData
	{
	public:
		// members
		ObjectRefHandle trap;		// 0x00
		REX::Float32 damage;		// 0x04
		REX::Float32 leveledDamage; // 0x08
		REX::Float32 minVelocity;	// 0x0C
		REX::Float32 pushBack;		// 0x10
		REX::Float32 deathPushback; // 0x14
		REX::Float32 stagger;		// 0x18
		bool continuous;			// 0x1C
		hkVector4 pushbackVector;	// 0x20
		hkVector4 hitLocation;		// 0x30
		std::uint32_t material;		// 0x40
	};

	static_assert(sizeof(TrapData) == 0x50);
}
