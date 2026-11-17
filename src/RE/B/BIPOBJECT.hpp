#pragma once

#include "RE/B/BGSObjectInstance.hpp"
#include "RE/B/BSModelDB.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/ModelReferenceEffect.hpp"
#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSObjectInstanceExtra;
	class BGSTextureSet;
	class NiAVObject;
	class ModelReferenceEffect;
	class TESModel;
	class WeaponAnimationGraphManagerHolder;

	class BIPOBJECT
	{
	public:
		// members
		BGSObjectInstance parent;											   // 0x00
		BGSObjectInstanceExtra* modExtra;									   // 0x10
		TESObjectARMA* armorAddon;											   // 0x18
		TESModel* part;														   // 0x20
		BGSTextureSet* skinTexture;											   // 0x28
		NiPointer<NiAVObject> partClone;									   // 0x30
		BSModelDB::HandelListHead handleList;								   // 0x38
		BSTSmartPointer<WeaponAnimationGraphManagerHolder> objectGraphManager; // 0x40
		NiPointer<ModelReferenceEffect> hitEffect;							   // 0x48
		bool skinned;														   // 0x50
	};

	static_assert(sizeof(BIPOBJECT) == 0x58);
}
