#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiAVObject;

	class SpectatorThreatInfo
	{
	public:
		enum class THREAT_LEVEL : std::int32_t
		{
			None = 0,
			MeleeWeapons = 1,
			ProjectileWeapons = 2,
			Explosion = 3,
			Insane = 4
		};

		// members
		ActorHandle source;								   // 0x00
		ActorHandle target;								   // 0x04
		REX::Enum<THREAT_LEVEL, std::int32_t> threatLevel; // 0x08
		std::time_t lastPerceivedTime;					   // 0x10
		REX::Float32 radius;							   // 0x18
		NiPoint3 lastKnownPosSource;					   // 0x1C
		NiPoint3 lastKnownPosTarget;					   // 0x28
		bool hasSource;									   // 0x34
		bool hasTarget;									   // 0x35
		NiPointer<NiAVObject> debugGeometry;			   // 0x38
	};

	static_assert(sizeof(SpectatorThreatInfo) == 0x40);
}
