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
#include "RE/N/NiPoint.hpp"
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

	class __declspec(novtable) TESRace
		: public TESForm,			 // 000
		  public TESFullName,		 // 020
		  public TESDescription,	 // 030
		  public TESSpellList,		 // 048
		  public BGSSkinForm,		 // 058
		  public BGSBipedObjectForm, // 068
		  public BGSKeywordForm,	 // 078
		  public BGSAttackDataForm,	 // 098
		  public BGSPropertySheet,	 // 0A8
		  public BGSPreloadable		 // 0B8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESRace };
		inline static constexpr auto VTABLE{ VTABLE::TESRace };
		inline static constexpr auto FORM_TYPE{ FormType::kRace };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class MOVEMENT_SPEED_OVERRIDE
		{
		public:
			// members
			BGSMovementType* moveType;		  // 00
			Movement::MaxSpeeds overrideData; // 08
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
			BSTHashMap<BSFixedString, BGSCharacterMorph::BoneBaseScales*> boneBaseScales;		// 00
			BSTHashMap<BSFixedString, BGSCharacterMorph::BONE_MODIFIER_MIN_MAX*> boneModifiers; // 30
		};
		static_assert(sizeof(BodyMorphData) == 0x60);

		~TESRace() override; // 00

		// members
		std::array<TESModel, std::to_underlying(SEX::kTotal)> skeletonModels;				 // 0C0
		std::array<TESModel, std::to_underlying(SEX::kTotal)> skeletonChargenModel;			 // 120
		RACE_DATA data;																		 // 180
		REX::Float32 clampFaceGeoValue;														 // 280
		REX::Float32 clampFaceGeoValue02;													 // 284
		std::array<BGSTextureModel, std::to_underlying(SEX::kTotal)> bodyTextureModels;		 // 288
		std::array<BGSBehaviorGraphModel, std::to_underlying(SEX::kTotal)> behaviorGraph;	 // 2E8
		std::array<BSFixedString, std::to_underlying(SEX::kTotal)> rootBehaviorGraphName;	 // 348
		std::array<BSFixedString, std::to_underlying(SEX::kTotal)> behaviorGraphProjectName; // 358
		std::array<BGSVoiceType*, std::to_underlying(SEX::kTotal)> defaultVoiceType;		 // 368
		BGSBodyPartData* bodyPartData;														 // 378
		BGSSoundTagComponent soundTagComponent;												 // 380
		BGSAttachParentArray attachParents;													 // 388
		BSFixedString formEditorID;															 // 3A0
		BGSMaterialType* bloodImpactMaterial;												 // 3A8
		BGSArtObject* dismemberBlood;														 // 3B0
		BGSTextureSet* meatCapTextureSet;													 // 3B8
		BGSTextureSet* meatCollarTextureSet;												 // 3C0
		BGSSoundDescriptorForm* corpseOpenSound;											 // 3C8
		BGSSoundDescriptorForm* corpseCloseSound;											 // 3D0
		std::array<BSFixedString, 32> bipedObjectNames;										 // 3D8
		std::array<ActorValueInfo*, 32> bipedObjectConditions;								 // 4D8
		BSTArray<EquipSlotData> equipSlotArray;												 // 5D8
		std::uint32_t validEquipTypes;														 // 5F0
		TESObjectWEAP* unarmedWeapon;														 // 5F8
		TESRace* morphRace;																	 // 600
		TESRace* armorParentRace;															 // 608
		TESQuest* dialogueQuest;															 // 610
		BSTArray<MOVEMENT_SPEED_OVERRIDE> speedOverrides;									 // 618
		BSTArray<BSFixedString> phonemeTargets;												 // 630
		BSTHashMap<std::uint32_t, BGSCharacterMorph::Slider*> morphSliders;					 // 648
		std::array<BGSMovementType*, 4> baseMoveTypes;										 // 678
		std::array<FaceRelatedData*, std::to_underlying(SEX::kTotal)> faceRelatedData;		 // 698
		std::array<BodyMorphData*, std::to_underlying(SEX::kTotal)> bodyMorphData;			 // 6A8
		TESTexture hairColorLookupTexture;													 // 6B8
		TESTexture hairColorLookupTextureExt;												 // 6C8
	};
	static_assert(sizeof(TESRace) == 0x6D8);
}
