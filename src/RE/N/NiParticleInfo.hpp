#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class NiParticleInfo
	{
	public:
		// members
		NiPoint3 velocity;				// 0x00
		REX::Float32 age;				// 0x0C
		REX::Float32 lifeSpan;			// 0x10
		REX::Float32 lastUpdate;		// 0x14
		std::uint16_t generation;		// 0x18
		std::uint16_t code;				// 0x1A
		std::int16_t subTexFrame;		// 0x1C
		std::uint16_t subTexFrameCount; // 0x1E
	};

	static_assert(sizeof(NiParticleInfo) == 0x20);
}
