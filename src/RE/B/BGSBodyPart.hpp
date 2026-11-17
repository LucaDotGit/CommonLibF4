#pragma once

#include "RE/B/BGSBodyPartDefs_HitReactionData.hpp"
#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/P/PART_DATA.hpp"
#include "RE/T/TESModel.hpp"

namespace RE
{
	class BGSBodyPart
	{
	public:
		// members
		BSFixedString nodeName;									 // 0x000
		BSFixedString targetName;								 // 0x008
		BSFixedString hitReactionVariablePrefix;				 // 0x010
		BGSBodyPartDefs::HitReactionData runtimeHitReactionData; // 0x018
		BGSLocalizedString partName;							 // 0x040
		BSFixedString goreObjectName;							 // 0x048
		TESModel explosionSpecialDebris;						 // 0x050
		PART_DATA data;											 // 0x080
		BGSArtObject* dismemberBlood;							 // 0x128
		BGSMaterialType* bloodImpactMaterial;					 // 0x130
		BGSMaterialType* onCrippleBloodImpactMaterial;			 // 0x138
		BGSTextureSet* meatCapTextureSet;						 // 0x140
		BGSTextureSet* meatCollarTextureSet;					 // 0x148
	};

	static_assert(sizeof(BGSBodyPart) == 0x150);
}
