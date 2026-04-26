#pragma once

#include "RE/N/NiPointer.hpp"

namespace RE::BGSBodyPartDefs
{
	enum class LIMB_ENUM : std::int32_t;
}

namespace RE
{
	class NiNode;

	class DeferredHideLimb
	{
	public:
		// members
		REX::Float32 dismemberTimer;								   // 00
		REX::Enum<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> limbIndex; // 04
		NiPointer<NiNode> dismemberedLimbRoot;						   // 08
		NiPointer<NiNode> replacementLimb;							   // 10
		DeferredHideLimb* next;										   // 18
		bool explosion;												   // 20
	};
	static_assert(sizeof(DeferredHideLimb) == 0x28);
}
