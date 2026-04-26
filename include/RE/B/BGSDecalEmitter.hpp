#pragma once

#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSTempEffectParticle;

	class BGSDecalEmitter
	{
	public:
		// members
		std::int32_t decalsToEmit;
		bool finished;
		BGSImpactData* decalImpactData;
		NiPointer<BSTempEffectParticle> particleData;
	};
	static_assert(sizeof(BGSDecalEmitter) == 0x18);
}
