#pragma once

#include "RE/B/BGSCharacterMorph_Transform.hpp"
#include "RE/B/BGSCharacterTint_EntrySlot.hpp"
#include "RE/B/BGSHeadPart.hpp"
#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"

namespace RE::BGSCharacterMorph
{
	class TransformMinMax;

	class FacialBoneRegion
	{
	public:
		// members
		Transform defaultTransform;								   // 0x00
		BGSLocalizedString name;								   // 0x28
		BSFixedString associatedMorphGroupName;					   // 0x30
		BGSCharacterTint::EntrySlot associatedTintSlot;			   // 0x38
		BGSHeadPart::HeadPartType associatedHeadPartType;		   // 0x3C
		BSTHashMap<BSFixedString, TransformMinMax*> boneMinMaxMap; // 0x40
		BSTArray<std::uint32_t> associatedMorphSliders;			   // 0x70
		std::uint32_t id;										   // 0x88
	};

	static_assert(sizeof(FacialBoneRegion) == 0x90);
}
