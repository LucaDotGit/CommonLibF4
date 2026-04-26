#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiAVObject;

	class SpectatorThreatInfo
	{
	public:
		enum class THREAT_LEVEL : std::int32_t
		{
			kNone = 0,
			kMeleeWeapons = 1,
			kProjectileWeapons = 2,
			kExplosion = 3,
			kInsane = 4
		};

		// members
		ActorHandle source;								   // 00
		ActorHandle target;								   // 04
		REX::Enum<THREAT_LEVEL, std::int32_t> threatLevel; // 08
		std::time_t lastPerceivedTime;					   // 10
		REX::Float32 radius;							   // 18
		NiPoint3 lastKnownPosSource;					   // 1C
		NiPoint3 lastKnownPosTarget;					   // 28
		bool hasSource;									   // 34
		bool hasTarget;									   // 35
		NiPointer<NiAVObject> debugGeometry;			   // 38
	};
	static_assert(sizeof(SpectatorThreatInfo) == 0x40);
}
