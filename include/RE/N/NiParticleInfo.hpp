#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class NiParticleInfo
	{
	public:
		// members
		NiPoint3 velocity;				// 00
		REX::Float32 age;				// 0C
		REX::Float32 lifeSpan;			// 10
		REX::Float32 lastUpdate;		// 14
		std::uint16_t generation;		// 18
		std::uint16_t code;				// 1A
		std::int16_t subTexFrame;		// 1C
		std::uint16_t subTexFrameCount; // 1E
	};
	static_assert(sizeof(NiParticleInfo) == 0x20);
}
