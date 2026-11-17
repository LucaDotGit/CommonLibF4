#pragma once

#include "RE/B/BGSAttachParentArray.hpp"
#include "RE/B/BGSAttackDataForm.hpp"
#include "RE/B/BGSBehaviorGraphModel.hpp"
#include "RE/B/BGSBipedObjectForm.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSPreloadable.hpp"
#include "RE/B/BGSPropertySheet.hpp"
#include "RE/B/BGSSkinForm.hpp"
#include "RE/B/BGSSoundTagComponent.hpp"
#include "RE/B/BGSTextureModel.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/M/Movement_MaxSpeeds.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/R/RACE_DATA.hpp"
#include "RE/S/SEX.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESModel.hpp"
#include "RE/T/TESSpellList.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE::BGSCharacterMorph
{
	class BONE_MODIFIER_MIN_MAX;
	class BoneBaseScales;
	class FacialBoneRegion;
	class Group;
	class Slider;
}

namespace RE::BGSCharacterTint::Template
{
	class Groups;
}

namespace RE
{
	class EquipSlotData;

	class __declspec(novtable) TESRace :
		public TESForm,			   // 0x000
		public TESFullName,		   // 0x020
		public TESDescription,	   // 0x030
		public TESSpellList,	   // 0x048
		public BGSSkinForm,		   // 0x058
		public BGSBipedObjectForm, // 0x068
		public BGSKeywordForm,	   // 0x078
		public BGSAttackDataForm,  // 0x098
		public BGSPropertySheet,   // 0x0A8
		public BGSPreloadable	   // 0x0B8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESRace;
		inline static constexpr const auto& VTABLE = VTABLE::TESRace;
		inline static constexpr auto FORM_TYPE = FormType::Race;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class MOVEMENT_SPEED_OVERRIDE
		{
		public:
			// members
			BGSMovementType* moveType;		  // 0x00
			Movement::MaxSpeeds overrideData; // 0x08
		};

		static_assert(sizeof(MOVEMENT_SPEED_OVERRIDE) == 0x78);

		class FaceRelatedData
		{
		public:
			// members
			BGSCharacterTint::Template::Groups* tintingTemplate;			   //
			BSTArray<BGSTextureSet*>* faceDetailsTextureSets;				   //
			BGSTextureSet* defaultFaceDetailsTextureSet;					   //
			BSTArray<TESNPC*>* presetNPCs;									   //
			BSTArray<BGSColorForm*>* availableHairColors;					   //
			BGSColorForm* defaultHairColor;									   //
			BSTArray<BGSHeadPart*>* headParts;								   //
			BSTArray<BGSCharacterMorph::Group*>* morphGroups;				   //
			BSTArray<BGSCharacterMorph::FacialBoneRegion*>* facialBoneRegions; //
			BGSCharacterMorph::FacialBoneRegion* neckFatFacialBoneRegion;	   //
			NiPoint3 neckFatAdjustmentScales;								   //
			BSFixedString wrinkleMapPath;									   //
		};

		static_assert(sizeof(FaceRelatedData) == 0x68);

		class BodyMorphData
		{
		public:
			// members
			BSTHashMap<BSFixedString, BGSCharacterMorph::BoneBaseScales*> boneBaseScales;		// 0x00
			BSTHashMap<BSFixedString, BGSCharacterMorph::BONE_MODIFIER_MIN_MAX*> boneModifiers; // 0x30
		};

		static_assert(sizeof(BodyMorphData) == 0x60);

		~TESRace() override; // 0x00

		// members
		std::array<TESModel, std::to_underlying(SEX::_Count)> skeletonModels;				 // 0x0C0
		std::array<TESModel, std::to_underlying(SEX::_Count)> skeletonChargenModel;			 // 0x120
		RACE_DATA data;																		 // 0x180
		REX::Float32 clampFaceGeoValue;														 // 0x280
		REX::Float32 clampFaceGeoValue02;													 // 0x284
		std::array<BGSTextureModel, std::to_underlying(SEX::_Count)> bodyTextureModels;		 // 0x288
		std::array<BGSBehaviorGraphModel, std::to_underlying(SEX::_Count)> behaviorGraph;	 // 0x2E8
		std::array<BSFixedString, std::to_underlying(SEX::_Count)> rootBehaviorGraphName;	 // 0x348
		std::array<BSFixedString, std::to_underlying(SEX::_Count)> behaviorGraphProjectName; // 0x358
		std::array<BGSVoiceType*, std::to_underlying(SEX::_Count)> defaultVoiceType;		 // 0x368
		BGSBodyPartData* bodyPartData;														 // 0x378
		BGSSoundTagComponent soundTagComponent;												 // 0x380
		BGSAttachParentArray attachParents;													 // 0x388
		BSFixedString formEditorID;															 // 0x3A0
		BGSMaterialType* bloodImpactMaterial;												 // 0x3A8
		BGSArtObject* dismemberBlood;														 // 0x3B0
		BGSTextureSet* meatCapTextureSet;													 // 0x3B8
		BGSTextureSet* meatCollarTextureSet;												 // 0x3C0
		BGSSoundDescriptorForm* corpseOpenSound;											 // 0x3C8
		BGSSoundDescriptorForm* corpseCloseSound;											 // 0x3D0
		std::array<BSFixedString, 32> bipedObjectNames;										 // 0x3D8
		std::array<ActorValueInfo*, 32> bipedObjectConditions;								 // 0x4D8
		BSTArray<EquipSlotData> equipSlotArray;												 // 0x5D8
		std::uint32_t validEquipTypes;														 // 0x5F0
		TESObjectWEAP* unarmedWeapon;														 // 0x5F8
		TESRace* morphRace;																	 // 0x600
		TESRace* armorParentRace;															 // 0x608
		TESQuest* dialogueQuest;															 // 0x610
		BSTArray<MOVEMENT_SPEED_OVERRIDE> speedOverrides;									 // 0x618
		BSTArray<BSFixedString> phonemeTargets;												 // 0x630
		BSTHashMap<std::uint32_t, BGSCharacterMorph::Slider*> morphSliders;					 // 0x648
		std::array<BGSMovementType*, 4> baseMoveTypes;										 // 0x678
		std::array<FaceRelatedData*, std::to_underlying(SEX::_Count)> faceRelatedData;		 // 0x698
		std::array<BodyMorphData*, std::to_underlying(SEX::_Count)> bodyMorphData;			 // 0x6A8
		TESTexture hairColorLookupTexture;													 // 0x6B8
		TESTexture hairColorLookupTextureExt;												 // 0x6C8
	};

	static_assert(sizeof(TESRace) == 0x6D8);
}
