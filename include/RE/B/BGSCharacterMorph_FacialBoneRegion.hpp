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
		Transform defaultTransform;								   // 00
		BGSLocalizedString name;								   // 28
		BSFixedString associatedMorphGroupName;					   // 30
		BGSCharacterTint::EntrySlot associatedTintSlot;			   // 38
		BGSHeadPart::HeadPartType associatedHeadPartType;		   // 3C
		BSTHashMap<BSFixedString, TransformMinMax*> boneMinMaxMap; // 40
		BSTArray<std::uint32_t> associatedMorphSliders;			   // 70
		std::uint32_t id;										   // 88
	};
	static_assert(sizeof(FacialBoneRegion) == 0x90);
}
