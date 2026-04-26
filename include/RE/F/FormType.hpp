#pragma once

namespace RE
{
	enum class FormType : std::int32_t
	{
		kNone,					  // 00 NONE X `TESForm`
								  //         X `BGSStoryManagerNodeBase`
								  //         X `BGSStoryManagerTreeForm`
								  //         X `MagicItem`
								  //         X `TESActorBase`
								  //         X `TESBoundAnimObject`
								  //         X `TESBoundObject`
								  //         X `TESObject`
		kPluginHeader,			  // 01 TES4 X
		kPluginGroup,			  // 02 GRUP X
		kGameSetting,			  // 03 GMST X
		kKeyword,				  // 04 KYWD X `BGSKeyword`
		kLocationRefType,		  // 05 LCRT X `BGSLocationRefType`
		kAction,				  // 06 AACT X `BGSAction`
		kTransform,				  // 07 TRNS X `BGSTransform`
		kComponent,				  // 08 CMPO X `BGSComponent`
		kTextureSet,			  // 09 TXST X `BGSTextureSet`
		kMenuIcon,				  // 0A MICN X `BGSMenuIcon`
		kGlobalVariable,		  // 0B GLOB X `TESGlobal`
		kDamageType,			  // 0C DMGT X `BGSDamageType`
		kClass,					  // 0D CLAS X `TESClass`
		kFaction,				  // 0E FACT X `TESFaction`
		kHeadPart,				  // 0F HDPT X `BGSHeadPart`
		kEyes,					  // 10 EYES X `TESEyes`
		kRace,					  // 11 RACE X `TESRace`
		kSoundMarker,			  // 12 SOUN X `TESSound`
		kAcousticSpace,			  // 13 ASPC X `BGSAcousticSpace`
		kSkill,					  // 14 SKIL X
		kMagicEffect,			  // 15 MGEF X `EffectSetting`
		kScript,				  // 16 SCPT X `Script`
		kLandscapeTexture,		  // 17 LTEX X TESLandTexture
		kEnchantment,			  // 18 ENCH X `EnchantmentItem`
		kSpell,					  // 19 SPEL X `SpellItem`
		kScroll,				  // 1A SCRL X `ScrollItem`
		kActivator,				  // 1B ACTI X `TESObjectACTI`
		kTalkingActivator,		  // 1C TACT X `BGSTalkingActivator`
		kArmor,					  // 1D ARMO X `TESObjectARMO`
		kBook,					  // 1E BOOK X `TESObjectBOOK`
		kContainer,				  // 1F CONT X `TESObjectCONT`
		kDoor,					  // 20 DOOR X `TESObjectDOOR`
		kIngredient,			  // 21 INGR X `IngredientItem`
		kLight,					  // 22 LIGH X `TESObjectLIGH`
		kMiscObject,			  // 23 MISC X `TESObjectMISC`
		kStatic,				  // 24 STAT X `TESObjectSTAT`
		kStaticCollection,		  // 25 SCOL X `BGSStaticCollection`
		kMovableStatic,			  // 26 MSTT X `BGSMovableStatic`
		kGrass,					  // 27 GRAS X `TESGrass`
		kTree,					  // 28 TREE X `TESObjectTREE`
		kFlora,					  // 29 FLOR X `TESFlora`
		kFurniture,				  // 2A FURN X `TESFurniture`
		kWeapon,				  // 2B WEAP X `TESObjectWEAP`
		kAmmo,					  // 2C AMMO X `TESAmmo`
		kActorBase,				  // 2D NPC_ X `TESNPC`
		kLeveledActor,			  // 2E LVLN X `TESLevCharacter`
		kKey,					  // 2F KEYM X `TESKey`
		kPotion,				  // 30 ALCH X `AlchemyItem`
		kIdleMarker,			  // 31 IDLM X `BGSIdleMarker`
		kNote,					  // 32 NOTE X `BGSNote`
		kProjectile,			  // 33 PROJ X `BGSProjectile`
		kHazard,				  // 34 HAZD X `BGSHazard`
		kBendableSpline,		  // 35 BNDS X `BGSBendableSpline`
		kSoulGem,				  // 36 SLGM X `TESSoulGem`
		kTerminal,				  // 37 TERM X `BGSTerminal`
		kLeveledItem,			  // 38 LVLI X `TESLevItem`
		kWeather,				  // 39 WTHR X `TESWeather`
		kClimate,				  // 3A CLMT X `TESClimate`
		kShaderParticleGeometry,  // 3B SPGD X `BGSShaderParticleGeometryData`
		kVisualEffect,			  // 3C RFCT X `BGSReferenceEffect`
		kRegion,				  // 3D REGN X `TESRegion`
		kNavMeshInfoMap,		  // 3E NAVI X `NavMeshInfoMap`
		kCell,					  // 3F CELL X `TESObjectCELL`
		kObjectReference,		  // 40 REFR X `TESObjectREFR`
								  //         X `Explosion`
								  //         X `Projectile`
		kActor,					  // 41 ACHR X `Actor`
								  //         X `PlayerCharacter`
		kMissileProjectile,		  // 42 PMIS X `MissileProjectile`
		kArrowProjectile,		  // 43 PARW X `ArrowProjectile`
		kGrenadeProjectile,		  // 44 PGRE X `GrenadeProjectile`
		kBeamProjectile,		  // 45 PBEA X `BeamProjectile`
		kFlameProjectile,		  // 46 PFLA X `FlameProjectile`
		kConeProjectile,		  // 47 PCON X `ConeProjectile`
		kBarrierProjectile,		  // 48 PBAR X `BarrierProjectile`
		kPlacedHazard,			  // 49 PHZD X `Hazard`
		kWorldSpace,			  // 4A WRLD X `TESWorldSpace`
		kLandscape,				  // 4B LAND X `TESObjectLAND`
		kNavMesh,				  // 4C NAVM X `NavMesh`
		kUnk4D,					  // 4D TLOD X
		kTopic,					  // 4E DIAL X `TESTopic`
		kTopicInfo,				  // 4F INFO X `TESTopicInfo`
		kQuest,					  // 50 QUST X `TESQuest`
		kIdle,					  // 51 IDLE X `TESIdleForm`
		kPackage,				  // 52 PACK X `TESPackage`
								  //         X `AlarmPackage`
								  //         X `DialoguePackage`
								  //         X `FleePackage`
								  //         X `SpectatorPackage`
								  //         X `TrespassPackage`
		kCombatStyle,			  // 53 CSTY X `TESCombatStyle`
		kLoadScreen,			  // 54 LSCR X `TESLoadScreen`
		kLeveledSpell,			  // 55 LVSP X `TESLevSpell`
		kAnimObject,			  // 56 ANIO X `TESObjectANIO`
		kWaterType,				  // 57 WATR X `TESWaterForm`
		kEffectShader,			  // 58 EFSH X `TESEffectShader`
		kOffsetTable,			  // 59 TOFT X
		kExplosion,				  // 5A EXPL X `BGSExplosion`
		kDebris,				  // 5B DEBR X `BGSDebris`
		kImageSpace,			  // 5C IMGS X `TESImageSpace`
		kImageSpaceModifier,	  // 5D IMAD X `TESImageSpaceModifier`
		kFormList,				  // 5E FLST X `BGSListForm`
		kPerk,					  // 5F PERK X `BGSPerk`
		kBodyPartData,			  // 60 BPTD X `BGSBodyPartData`
		kAddonNode,				  // 61 ADDN X `BGSAddonNode`
		kActorValue,			  // 62 AVIF X `ActorValueInfo`
		kCameraShot,			  // 63 CAMS X `BGSCameraShot`
		kCameraPath,			  // 64 CPTH X `BGSCameraPath`
		kVoiceType,				  // 65 VTYP X `BGSVoiceType`
		kMaterialType,			  // 66 MATT X `BGSMaterialType`
		kImpactData,			  // 67 IPCT X `BGSImpactData`
		kImpactDataSet,			  // 68 IPDS X `BGSImpactDataSet`
		kArmorAddon,			  // 69 ARMA X `TESObjectARMA`
		kEncounterZone,			  // 6A ECZN X `BGSEncounterZone`
		kLocation,				  // 6B LCTN X `BGSLocation`
		kMessage,				  // 6C MESG X `BGSMessage`
		kRagdoll,				  // 6D RGDL X
		kDefaultObjectManager,	  // 6E DOBJ X `BGSDefaultObjectManager`
		kDefaultObject,			  // 6F DFOB X `BGSDefaultObject`
		kLightingTemplate,		  // 70 LGTM X `BGSLightingTemplate`
		kMusicType,				  // 71 MUSC X `BGSMusicType`
		kFootstep,				  // 72 FSTP X `BGSFootstep`
		kFootstepSet,			  // 73 FSTS X `BGSFootstepSet`
		kStoryManagerBranchNode,  // 74 SMBN X `BGSStoryManagerBranchNode`
		kStoryManagerQuestNode,	  // 75 SMQN X `BGSStoryManagerQuestNode`
		kStoryManagerEventNode,	  // 76 SMEN X `BGSStoryManagerEventNode`
		kDialogueBranch,		  // 77 DLBR X `BGSDialogueBranch`
		kMusicTrack,			  // 78 MUST X `BGSMusicTrackFormWrapper`
		kDialogueView,			  // 79 DLVW X
		kWordOfPower,			  // 7A WOOP X `TESWordOfPower`
		kShout,					  // 7B SHOU X `TESShout`
		kEquipSlot,				  // 7C EQUP X `BGSEquipSlot`
		kRelationship,			  // 7D RELA X `BGSRelationship`
		kScene,					  // 7E SCEN X `BGSScene`
		kAssociationType,		  // 7F ASTP X `BGSAssociationType`
		kOutfit,				  // 80 OTFT X `BGSOutfit`
		kArtObject,				  // 81 ARTO X `BGSArtObject`
		kMaterialObject,		  // 82 MATO X `BGSMaterialObject`
		kMovementType,			  // 83 MOVT X `BGSMovementType`
		kSoundDescriptor,		  // 84 SNDR X `BGSSoundDescriptorForm`
		kDualCastData,			  // 85 DUAL X `BGSDualCastData`
		kSoundCategory,			  // 86 SNCT X `BGSSoundCategory`
		kSoundOutput,			  // 87 SOPM X `BGSSoundOutput`
		kCollisionLayer,		  // 88 COLL X `BGSCollisionLayer`
		kColorForm,				  // 89 CLFM X `BGSColorForm`
		kReverbParameters,		  // 8A REVB X `BGSReverbParameters`
		kPackIn,				  // 8B PKIN X `BGSPackIn`
		kReferenceGroup,		  // 8C RFGP X `BGSReferenceGroup`
		kAimModel,				  // 8D AMDL X `BGSAimModel`
		kLayer,					  // 8E LAYR X
		kConstructibleObject,	  // 8F COBJ X `BGSConstructibleObject`
		kObjectMod,				  // 90 OMOD X `BGSMod::Attachment::Mod`
		kMaterialSwap,			  // 91 MSWP X `BGSMaterialSwap`
		kZoomData,				  // 92 ZOOM X `BGSZoomData`
		kInstanceNamingRules,	  // 93 INNR X `BGSInstanceNamingRules`
		kSoundKeywordMapping,	  // 94 KSSM X `BGSSoundKeywordMapping`
		kAudioEffectChain,		  // 95 AECH X `BGSAudioEffectChain`
		kSceneCollection,		  // 96 SCCO X
		kAttractionRule,		  // 97 AORU X `BGSAttractionRule`
		kSoundCategorySnapshot,	  // 98 SCSN X `BGSSoundCategorySnapshot`
		kSoundTagSet,			  // 99 STAG X `BGSSoundTagSet`
		kNavMeshObstacleManager,  // 9A NOCM X `NavMeshObstacleCoverManager`
		kLensFlare,				  // 9B LENS X `BGSLensFlare`
		kLensSprite,			  // 9C LSPR X
		kGodRays,				  // 9D GDRY X `BGSGodRays`
		kObjectVisibilityManager, // 9E OVIS X `BGSObjectVisibilityManager`

		kTotal, // 9F

		kBaseAlias,			 // A0 X `BGSBaseAlias`
		kRefAlias,			 // A1 X `BGSRefAlias`
		kLocationAlias,		 // A2 X `BGSLocAlias`
		kActiveEffect,		 // A3 X `ActiveEffect`
		kInputEnableLayer,	 // A4 X `BSInputEnableLayer`
		kRefCollectionAlias, // A5 X `BGSRefCollectionAlias`

		kScriptObject = -1, // FFFFFFFF X `BSScript::Object`

		kMin = kNone,
		kMax = kObjectVisibilityManager
	};
}
