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
		BGSObjectInstance parent;											   // 00
		BGSObjectInstanceExtra* modExtra;									   // 10
		TESObjectARMA* armorAddon;											   // 18
		TESModel* part;														   // 20
		BGSTextureSet* skinTexture;											   // 28
		NiPointer<NiAVObject> partClone;									   // 30
		BSModelDB::HandelListHead handleList;								   // 38
		BSTSmartPointer<WeaponAnimationGraphManagerHolder> objectGraphManager; // 40
		NiPointer<ModelReferenceEffect> hitEffect;							   // 48
		bool skinned;														   // 50
	};
	static_assert(sizeof(BIPOBJECT) == 0x58);
}
