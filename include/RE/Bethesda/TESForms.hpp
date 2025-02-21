#pragma once

#include "RE/Bethesda/Atomic.hpp"
#include "RE/Bethesda/BGSBodyPartDefs.hpp"
#include "RE/Bethesda/BSBitField.hpp"
#include "RE/Bethesda/BSContainer.hpp"
#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSPointerHandle.hpp"
#include "RE/Bethesda/BSString.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/BSTList.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"
#include "RE/Bethesda/BSTTuple.hpp"
#include "RE/Bethesda/FormComponents.hpp"
#include "RE/Bethesda/ImageSpaceData.hpp"
#include "RE/Bethesda/MagicSystem.hpp"
#include "RE/Bethesda/Movement.hpp"
#include "RE/Bethesda/Settings.hpp"
#include "RE/Bethesda/SoundLevels.hpp"
#include "RE/Bethesda/TESCondition.hpp"
#include "RE/Bethesda/TESFile.hpp"
#include "RE/Bethesda/bhkPickData.hpp"
#include "RE/NetImmerse/NiColor.hpp"
#include "RE/NetImmerse/NiFlags.hpp"
#include "RE/NetImmerse/NiPoint.hpp"
#include "RE/NetImmerse/NiSmartPointer.hpp"

namespace RE
{
	class TESRegionList;
	class TESForm;
	class TESObject;
	class TESBoundObject;
	class MagicItem;
	class TESBoundAnimObject;
	class TESActorBase;
	class BGSStoryManagerTreeForm;
	class BGSStoryManagerNodeBase;
	class BGSKeyword;
	class BGSLocationRefType;
	class BGSAction;
	class BGSTransform;
	class BGSComponent;
	class BGSTextureSet;
	class BGSMenuIcon;
	class TESGlobal;
	class BGSDamageType;
	class TESClass;
	class TESFaction;
	class BGSHeadPart;
	class TESEyes;
	class TESRace;
	class TESSound;
	class BGSAcousticSpace;
	class EffectSetting;
	class Script;
	class TESLandTexture;
	class EnchantmentItem;
	class SpellItem;
	class ScrollItem;
	class TESObjectACTI;
	class BGSTalkingActivator;
	class TESObjectARMO;
	class TESObjectBOOK;
	class TESObjectCONT;
	class TESObjectDOOR;
	class IngredientItem;
	class TESObjectLIGH;
	class TESObjectMISC;
	class TESObjectSTAT;
	class BGSStaticCollection;
	class BGSMovableStatic;
	class TESGrass;
	class TESObjectTREE;
	class TESFlora;
	class TESFurniture;
	class TESObjectWEAP;
	class TESAmmo;
	class TESNPC;
	class TESLevCharacter;
	class TESKey;
	class AlchemyItem;
	class BGSIdleMarker;
	class BGSNote;
	class BGSProjectile;
	class BGSHazard;
	class BGSBendableSpline;
	class TESSoulGem;
	class BGSTerminal;
	class TESLevItem;
	class TESWeather;
	class TESClimate;
	class BGSShaderParticleGeometryData;
	class BGSReferenceEffect;
	class TESRegion;
	class NavMeshInfoMap;
	class TESObjectCELL;
	class Actor;
	class PlayerCharacter;
	class MissileProjectile;
	class ArrowProjectile;
	class GrenadeProjectile;
	class BeamProjectile;
	class FlameProjectile;
	class ConeProjectile;
	class BarrierProjectile;
	class TESObjectREFR;
	class Explosion;
	class Projectile;
	class TESWorldSpace;
	class TESObjectLAND;
	class NavMesh;
	class TESTopic;
	class TESTopicInfo;
	class TESQuest;
	class TESIdleForm;
	class TESPackage;
	class AlarmPackage;
	class DialoguePackage;
	class FleePackage;
	class SpectatorPackage;
	class TrespassPackage;
	class TESCombatStyle;
	class TESLoadScreen;
	class TESLevSpell;
	class TESObjectANIO;
	class TESWaterForm;
	class TESEffectShader;
	class BGSExplosion;
	class BGSDebris;
	class TESImageSpace;
	class TESImageSpaceModifier;
	class BGSListForm;
	class BGSPerk;
	class BGSBodyPartData;
	class BGSAddonNode;
	class ActorValueInfo;
	class BGSCameraShot;
	class BGSCameraPath;
	class BGSVoiceType;
	class BGSMaterialType;
	class BGSImpactData;
	class BGSImpactDataSet;
	class TESObjectARMA;
	class BGSEncounterZone;
	class BGSLocation;
	class BGSMessage;
	class BGSDefaultObjectManager;
	class BGSDefaultObject;
	class BGSLightingTemplate;
	class BGSMusicType;
	class BGSFootstep;
	class BGSFootstepSet;
	class BGSStoryManagerBranchNode;
	class BGSStoryManagerQuestNode;
	class BGSStoryManagerEventNode;
	class BGSDialogueBranch;
	class BGSMusicTrackFormWrapper;
	class TESWordOfPower;
	class TESShout;
	class BGSEquipSlot;
	class BGSRelationship;
	class BGSScene;
	class BGSAssociationType;
	class BGSOutfit;
	class BGSArtObject;
	class BGSMaterialObject;
	class BGSMovementType;
	class BGSSoundDescriptorForm;
	class BGSDualCastData;
	class BGSSoundCategory;
	class BGSSoundOutput;
	class BGSCollisionLayer;
	class BGSColorForm;
	class BGSReverbParameters;
	class BGSPackIn;
	class BGSAimModel;
	class BGSConstructibleObject;
	class BGSMaterialSwap;
	class BGSZoomData;
	class BGSInstanceNamingRules;
	class BGSSoundKeywordMapping;
	class BGSAudioEffectChain;
	class BGSAttractionRule;
	class BGSSoundCategorySnapshot;
	class BGSSoundTagSet;
	class BGSLensFlare;
	class BGSGodRays;
	class bhkWorld;

	namespace BGSMod::Attachment
	{
		class Mod;
	}

	enum class ENUM_FORMTYPE
	{
		kNONE, // 00 NONE X TESForm
			   //         X TESObject
			   //         X TESBoundObject
			   //         X MagicItem
			   //         X TESBoundAnimObject
			   //         X TESActorBase
			   //         X BGSStoryManagerTreeForm
			   //         X BGSStoryManagerNodeBase
		kTES4, // 01 TES4
		kGRUP, // 02 GRUP
		kGMST, // 03 GMST
		kKYWD, // 04 KYWD X BGSKeyword
		kLCRT, // 05 LCRT X BGSLocationRefType
		kAACT, // 06 AACT X BGSAction
		kTRNS, // 07 TRNS X BGSTransform
		kCMPO, // 08 CMPO X BGSComponent
		kTXST, // 09 TXST X BGSTextureSet
		kMICN, // 0A MICN X BGSMenuIcon
		kGLOB, // 0B GLOB X TESGlobal
		kDMGT, // 0C DMGT X BGSDamageType
		kCLAS, // 0D CLAS X TESClass
		kFACT, // 0E FACT X TESFaction
		kHDPT, // 0F HDPT X BGSHeadPart
		kEYES, // 10 EYES X TESEyes
		kRACE, // 11 RACE X TESRace
		kSOUN, // 12 SOUN X TESSound
		kASPC, // 13 ASPC X BGSAcousticSpace
		kSKIL, // 14 SKIL
		kMGEF, // 15 MGEF X EffectSetting
		kSCPT, // 16 SCPT X Script
		kLTEX, // 17 LTEX X TESLandTexture
		kENCH, // 18 ENCH X EnchantmentItem
		kSPEL, // 19 SPEL X SpellItem
		kSCRL, // 1A SCRL X ScrollItem
		kACTI, // 1B ACTI X TESObjectACTI
		kTACT, // 1C TACT X BGSTalkingActivator
		kARMO, // 1D ARMO X TESObjectARMO
		kBOOK, // 1E BOOK X TESObjectBOOK
		kCONT, // 1F CONT X TESObjectCONT
		kDOOR, // 20 DOOR X TESObjectDOOR
		kINGR, // 21 INGR X IngredientItem
		kLIGH, // 22 LIGH X TESObjectLIGH
		kMISC, // 23 MISC X TESObjectMISC
		kSTAT, // 24 STAT X TESObjectSTAT
		kSCOL, // 25 SCOL X BGSStaticCollection
		kMSTT, // 26 MSTT X BGSMovableStatic
		kGRAS, // 27 GRAS X TESGrass
		kTREE, // 28 TREE X TESObjectTREE
		kFLOR, // 29 FLOR X TESFlora
		kFURN, // 2A FURN X TESFurniture
		kWEAP, // 2B WEAP X TESObjectWEAP
		kAMMO, // 2C AMMO X TESAmmo
		kNPC_, // 2D NPC_ X TESNPC
		kLVLN, // 2E LVLN X TESLevCharacter
		kKEYM, // 2F KEYM X TESKey
		kALCH, // 30 ALCH X AlchemyItem
		kIDLM, // 31 IDLM X BGSIdleMarker
		kNOTE, // 32 NOTE X BGSNote
		kPROJ, // 33 PROJ X BGSProjectile
		kHAZD, // 34 HAZD X BGSHazard
		kBNDS, // 35 BNDS X BGSBendableSpline
		kSLGM, // 36 SLGM X TESSoulGem
		kTERM, // 37 TERM X BGSTerminal
		kLVLI, // 38 LVLI X TESLevItem
		kWTHR, // 39 WTHR X TESWeather
		kCLMT, // 3A CLMT X TESClimate
		kSPGD, // 3B SPGD X BGSShaderParticleGeometryData
		kRFCT, // 3C RFCT X BGSReferenceEffect
		kREGN, // 3D REGN X TESRegion
		kNAVI, // 3E NAVI X NavMeshInfoMap
		kCELL, // 3F CELL X TESObjectCELL
		kREFR, // 40 REFR X TESObjectREFR
			   //         X Explosion
			   //         X Projectile
		kACHR, // 41 ACHR X Actor
			   //         X PlayerCharacter
		kPMIS, // 42 PMIS X MissileProjectile
		kPARW, // 43 PARW X ArrowProjectile
		kPGRE, // 44 PGRE X GrenadeProjectile
		kPBEA, // 45 PBEA X BeamProjectile
		kPFLA, // 46 PFLA X FlameProjectile
		kPCON, // 47 PCON X ConeProjectile
		kPBAR, // 48 PBAR X BarrierProjectile
		kPHZD, // 49 PHZD X Hazard
		kWRLD, // 4A WRLD X TESWorldSpace
		kLAND, // 4B LAND X TESObjectLAND
		kNAVM, // 4C NAVM X NavMesh
		kTLOD, // 4D TLOD
		kDIAL, // 4E DIAL X TESTopic
		kINFO, // 4F INFO X TESTopicInfo
		kQUST, // 50 QUST X TESQuest
		kIDLE, // 51 IDLE X TESIdleForm
		kPACK, // 52 PACK X TESPackage
			   //         X AlarmPackage
			   //         X DialoguePackage
			   //         X FleePackage
			   //         X SpectatorPackage
			   //         X TrespassPackage
		kCSTY, // 53 CSTY X TESCombatStyle
		kLSCR, // 54 LSCR X TESLoadScreen
		kLVSP, // 55 LVSP X TESLevSpell
		kANIO, // 56 ANIO X TESObjectANIO
		kWATR, // 57 WATR X TESWaterForm
		kEFSH, // 58 EFSH X TESEffectShader
		kTOFT, // 59 TOFT
		kEXPL, // 5A EXPL X BGSExplosion
		kDEBR, // 5B DEBR X BGSDebris
		kIMGS, // 5C IMGS X TESImageSpace
		kIMAD, // 5D IMAD X TESImageSpaceModifier
		kFLST, // 5E FLST X BGSListForm
		kPERK, // 5F PERK X BGSPerk
		kBPTD, // 60 BPTD X BGSBodyPartData
		kADDN, // 61 ADDN X BGSAddonNode
		kAVIF, // 62 AVIF X ActorValueInfo
		kCAMS, // 63 CAMS X BGSCameraShot
		kCPTH, // 64 CPTH X BGSCameraPath
		kVTYP, // 65 VTYP X BGSVoiceType
		kMATT, // 66 MATT X BGSMaterialType
		kIPCT, // 67 IPCT X BGSImpactData
		kIPDS, // 68 IPDS X BGSImpactDataSet
		kARMA, // 69 ARMA X TESObjectARMA
		kECZN, // 6A ECZN X BGSEncounterZone
		kLCTN, // 6B LCTN X BGSLocation
		kMESG, // 6C MESG X BGSMessage
		kRGDL, // 6D RGDL
		kDOBJ, // 6E DOBJ X BGSDefaultObjectManager
		kDFOB, // 6F DFOB X BGSDefaultObject
		kLGTM, // 70 LGTM X BGSLightingTemplate
		kMUSC, // 71 MUSC X BGSMusicType
		kFSTP, // 72 FSTP X BGSFootstep
		kFSTS, // 73 FSTS X BGSFootstepSet
		kSMBN, // 74 SMBN X BGSStoryManagerBranchNode
		kSMQN, // 75 SMQN X BGSStoryManagerQuestNode
		kSMEN, // 76 SMEN X BGSStoryManagerEventNode
		kDLBR, // 77 DLBR X BGSDialogueBranch
		kMUST, // 78 MUST X BGSMusicTrackFormWrapper
		kDLVW, // 79 DLVW
		kWOOP, // 7A WOOP X TESWordOfPower
		kSHOU, // 7B SHOU X TESShout
		kEQUP, // 7C EQUP X BGSEquipSlot
		kRELA, // 7D RELA X BGSRelationship
		kSCEN, // 7E SCEN X BGSScene
		kASTP, // 7F ASTP X BGSAssociationType
		kOTFT, // 80 OTFT X BGSOutfit
		kARTO, // 81 ARTO X BGSArtObject
		kMATO, // 82 MATO X BGSMaterialObject
		kMOVT, // 83 MOVT X BGSMovementType
		kSNDR, // 84 SNDR X BGSSoundDescriptorForm
		kDUAL, // 85 DUAL X BGSDualCastData
		kSNCT, // 86 SNCT X BGSSoundCategory
		kSOPM, // 87 SOPM X BGSSoundOutput
		kCOLL, // 88 COLL X BGSCollisionLayer
		kCLFM, // 89 CLFM X BGSColorForm
		kREVB, // 8A REVB X BGSReverbParameters
		kPKIN, // 8B PKIN X BGSPackIn
		kRFGP, // 8C RFGP
		kAMDL, // 8D AMDL X BGSAimModel
		kLAYR, // 8E LAYR
		kCOBJ, // 8F COBJ X BGSConstructibleObject
		kOMOD, // 90 OMOD X BGSMod::Attachment::Mod
		kMSWP, // 91 MSWP X BGSMaterialSwap
		kZOOM, // 92 ZOOM X BGSZoomData
		kINNR, // 93 INNR X BGSInstanceNamingRules
		kKSSM, // 94 KSSM X BGSSoundKeywordMapping
		kAECH, // 95 AECH X BGSAudioEffectChain
		kSCCO, // 96 SCCO
		kAORU, // 97 AORU X BGSAttractionRule
		kSCSN, // 98 SCSN X BGSSoundCategorySnapshot
		kSTAG, // 99 STAG X BGSSoundTagSet
		kNOCM, // 9A NOCM
		kLENS, // 9B LENS X BGSLensFlare
		kLSPR, // 9C LSPR
		kGDRY, // 9D GDRY X BGSGodRays
		kOVIS, // 9E OVIS

		kTotal,
		kActiveEffect = 163
	};

	enum class _D3DBLEND;	// NOLINT(bugprone-reserved-identifier)
	enum class _D3DBLENDOP; // NOLINT(bugprone-reserved-identifier)
	enum class _D3DCMPFUNC; // NOLINT(bugprone-reserved-identifier)
	enum class CHUNK_ID;
	enum class COMMAND_REFUSAL_TYPE;

	namespace BGSMod::Template
	{
		class Items;
	}

	namespace EffectArchetypes
	{
		enum class ArchetypeID : std::int32_t
		{
			kNone = -1,
			kValueModifier = 0,
			kScript = 1,
			kDispel = 2,
			kCureDisease = 3,
			kAbsorb = 4,
			kDualValueModifier = 5,
			kCalm = 6,
			kDemoralize = 7,
			kFrenzy = 8,
			kDisarm = 9,
			kCommandSummoned = 10,
			kInvisibility = 11,
			kLight = 12,
			kDarkness = 13,
			kNightEye = 14,
			kLock = 15,
			kOpen = 16,
			kBoundWeapon = 17,
			kSummonCreature = 18,
			kDetectLife = 19,
			kTelekinesis = 20,
			kParalyze = 21,
			kReanimate = 22,
			kSoulTrap = 23,
			kTurnUndead = 24,
			kGuide = 25,
			kUnused01 = 26,
			kCureParalysis = 27,
			kCureAddiction = 28,
			kCurePoison = 29,
			kConcussion = 30,
			kStimpak = 31,
			kAccumulatingMagnitude = 32,
			kStagger = 33,
			kPeakValueModifier = 34,
			kCloak = 35,
			kUnused02 = 36,
			kSlowTime = 37,
			kRally = 38,
			kEnhanceWeapon = 39,
			kSpawnHazard = 40,
			kEtherealize = 41,
			kBanish = 42,
			kSpawnScriptedRef = 43,
			kDisguise = 44,
			kDamage = 45,
			kImmunity = 46,
			kPermanentReanimate = 47,
			kJetpack = 48,
			kChameleon = 49,
		};
	}

	class BGSLoadFormBuffer;
	class BGSLoadGameBuffer;
	class BGSMusicTrack;
	class BGSPerkEntry;
	class BGSPreviewTransform;
	class BGSSaveFormBuffer;
	class BGSSceneAction;
	class BGSSoundDescriptor;
	class BSGeometry;
	class BSMultiBoundNode;
	class BSPortalGraph;
	class BSIAudioEffectParameters;
	class BSLensFlareSpriteRenderData;
	class ExtraDataList;
	class NavMeshArray;
	class NiColorInterpolator;
	class NiFloatInterpolator;
	class NiFormArray;
	class NiNode;
	class NiTexture;
	class QueuedFile;
	class QueuedPromoteLocationReferencesTask;
	class TBO_InstanceData;
	class TESPackageData;
	class TESRegionDataList;
	class TESRegionPointList;

	struct BGSDebrisData;
	struct FORM;
	struct FORM_GROUP;
	struct EXTERIOR_DATA;
	struct OverrideData;

	namespace BGSWaterCollisionManager
	{
		class AutoWater;
		class BGSWaterUpdateI;
	}

	struct FORM_FLAG
	{
		enum FORM_FLAGS : std::uint32_t
		{
			kNone,
			kDestructible = 1 << 0,
			kMaster = 1 << 0,
			kUnlocked = 1 << 0,

			kAltered = 1 << 1,
			kPlayable = 1 << 2,
			kInitialized = 1 << 3,
			kNonOccluder = 1 << 4,
			kDeleted = 1 << 5,

			kBorderRegion = 1 << 6,
			kGlobalConstant = 1 << 6,
			kHasSpokenFlag = 1 << 6,
			kKnown = 1 << 6,
			kInPlaceableWater = 1 << 6,

			kFireOff = 1 << 7,
			kMustUpdate = 1 << 8,
			kOnLocalMap = 1 << 9,
			kPersistent = 1 << 10,

			kDisabled = 1 << 11,
			kUsedAsMovingPlatform = 1 << 11,

			kIgnored = 1 << 12,

			kEmpty = 1 << 13,
			kResetDestruction = 1 << 13,

			kTemporary = 1 << 14,
			kPartialForm = 1 << 14,

			kMustBeVisibleDistant = 1 << 15,
			kRestricted = 1 << 15,

			kRandomAnim = 1 << 16,
			kDangerous = 1 << 17,
			kHasCurrents = 1 << 19,
			kIgnoreFriendlyHits = 1 << 20,
			kStillLoading = 1 << 21,
			kFormRetainsID = 1 << 22,
			kDestroyed = 1 << 23,
			kUnk24 = 1 << 24,

			kNoAIAcquire = 1 << 25,
			kObstacle = 1 << 25,

			kVATSTargetOverride = 1 << 26,
			kDisableFade = 1 << 27,

			kReflectedByAutoWater = 1 << 28,
			kShowOnWorldMap = 1 << 28,

			kChildCanUse = 1 << 29,

			kNavMeshGeneration_Filter = 1 << 26,
			kNavMeshGeneration_BoundingBox = 1 << 27,
			kNavMeshGeneration_Ground = 1 << 30
		};
	};
	using FORM_FLAGS = FORM_FLAG::FORM_FLAGS;

	struct CHANGE_TYPES
	{
		enum CHANGE_TYPE : std::uint32_t
		{
			kFormCreated = 0,
			kFormFlags = 1u << 0,
			kRefrMove = 1u << 1,
			kRefrHavokMove = 1u << 2,
			kRefrCellChange = 1u << 3,
			kRefrScale = 1u << 4,
			kRefrInventory = 1u << 5,
			kRefrExtraOwnership = 1u << 6,
			kRefrBaseObject = 1u << 7,
			kRefrExtraLinkRef = 1u << 8,
			kRefrExtraWorkshop = 1u << 9,
			kRefrExtraGameOnly = 1u << 31,
			kRefrExtraCreatedOnly = 1u << 30,
			kRefrExtraEncounterZone = 1u << 29,
			kRefrAnimation = 1u << 28,
			kRefrLeveledInventory = 1u << 27,
			kRefrExtraActivatingChildren = 1u << 26,
			kRefrPromoted = 1u << 25,
			kActorLifestate = 1u << 10,
			kActorExtraPackageData = 1u << 11,
			kActorExtraMerchantContainer = 1u << 12,
			kActorPermanentModifiers = 1u << 23,
			kActorOverrideModifiers = 1u << 22,
			kActorDamageModifiers = 1u << 21,
			kActorTempModifiers = 1u << 20,
			kActorDispositionModifiers = 1u << 19,
			kActorExtraLeveledActor = 1u << 18,
			kActorExtraDismemberedLimbs = 1u << 17,
			kObjectExtraItemData = 1u << 10,
			kObjectExtraAmmo = 1u << 11,
			kObjectExtraLock = 1u << 12,
			kObjectForceMove = 1u << 13,
			kObjectOpenState = 1u << 23,
			kObjectOpenDefaultState = 1u << 22,
			kObjectEmpty = 1u << 21,
			kDoorExtraTeleport = 1u << 17,
			kQuestFlags = 1u << 1,
			kQuestScriptDelay = 1u << 2,
			kQuestStages = 1u << 31,
			kQuestScript = 1u << 30,
			kQuestObjectives = 1u << 29,
			kQuestRunData = 1u << 28,
			kQuestInstances = 1u << 27,
			kQuestAlreadyRun = 1u << 26,
			kTopicSaidPlayer = 1u << 30,
			kTopicSaidOnce = 1u << 31,
			kRelationshipData = 1u << 1,
			kLocationSpecRefs = 1u < 28,
			kLocationNewRefs = 1u << 29,
			kLocationKeywordData = 1u << 30,
			kLocationCleared = 1u << 31,
			kNoteRead = 1u << 31,
			kCellSeenData = 1u << 31,
			kCellDetachTime = 1u << 30,
			kCellExteriorChar = 1u << 29,
			kCellExteriorShort = 1u << 28,
			kCellFlags = 1u << 1,
			kCellFullname = 1u << 2,
			kCellOwnership = 1u << 3,
			kFactionFlags = 1u << 1,
			kFactionReactions = 1u << 2,
			kFactionVendorData = 1u << 30,
			kFactionCrimeCounts = 1u << 31,
			kPackageNeverRun = 1u << 31,
			kPackageWaiting = 1u << 30,
			kBaseObjectValue = 1u << 1,
			kBaseObjectFullName = 1u << 2,
			kBookTeaches = 1u << 5,
			kBookRead = 1u << 6,
			kTalkingActivatorSpeaker = 1u << 23,
			kActorBaseData = 1u << 1,
			kActorBaseAttributes = 1u << 2,
			kActorBaseAIData = 1u << 3,
			kActorBaseSpellList = 1u << 4,
			kActorBaseFullName = 1u << 5,
			kActorBaseFactions = 1u << 6,
			kNPCSkills = 1u << 9,
			kNPCClass = 1u << 10,
			kNPCFace = 1u << 11,
			kNPCDefaultOutfit = 1u << 12,
			kNPCSleepOutfit = 1u << 13,
			kNPCBodyScales = 1u << 14,
			kNPCRace = 1u << 25,
			kNPCGender = 1u << 24,
			kCreatureSkills = 1u << 9,
			kClassTagSkills = 1u << 1,
			kEncounterZoneFlags = 1u << 1,
			kEncounterZoneGameData = 1u << 31,
			kQuestNodeRunTime = 1u << 31,
			kSceneActive = 1u << 31,
			kFormListAddedForm = 1u << 31,
			kLeveledListAddedObject = 1u << 31,
			kIngredientUse = 1u << 31,
			kINRMergeTarget = 1u << 31
		};
	};
	using CHANGE_TYPE = CHANGE_TYPES::CHANGE_TYPE;

	struct FORM_ENUM_STRING
	{
	public:
		// members
		ENUM_FORMTYPE formID;	// 00
		const char* formString; // 08 - "GRUP"
		std::uint32_t formCode; // 10 - 'PURG'
	};
	static_assert(sizeof(FORM_ENUM_STRING) == 0x18);

	class TESFileArray
		: public BSStaticArray<TESFile*> // 00
	{
	public:
	};
	static_assert(sizeof(TESFileArray) == 0x10);

	struct TESFileContainer
	{
	public:
		// members
		const TESFileArray* array; // 00
	};
	static_assert(sizeof(TESFileContainer) == 0x8);

	class __declspec(novtable) TESForm
		: public BaseFormComponent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESForm };
		inline static constexpr auto VTABLE{ VTABLE::TESForm };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kNONE };

		struct FormSortFunc
		{
		public:
			std::int32_t operator()(const TESForm* a_arg1, const TESForm* a_arg2)
			{
				using func_t = decltype(&FormSortFunc::operator());
				static REL::Relocation<func_t> func{ REL::ID(705530) };
				return func(this, a_arg1, a_arg2);
			}
		};
		static_assert(std::is_empty_v<FormSortFunc>);

		enum class InGameFormFlags
		{
			kNone = 0,
			kWantsDelete = 1 << 0,
			kForcedPersistent = 1 << 1,
			kNoFavorAllowed = 1 << 4,
			kIsSkyObject = 1 << 5,
			kRefOriginalPersistent = 1 << 6,
			kRefPermanentlyDeleted = 1 << 7
		};

		~TESForm() override; // 00

		// override (BaseFormComponent)
		std::uint32_t GetFormComponentType() const override;	   // 01
		void InitializeDataComponent() override;				   // 02
		void ClearDataComponent() override;						   // 03
		void InitComponent() override;							   // 04
		void CopyComponent(BaseFormComponent*, TESForm*) override; // 05
		void CopyComponent(BaseFormComponent*) override;		   // 06

		// add
		virtual void InitializeData() { return; }																																													 // 07
		virtual void ClearData() { return; }																																														 // 08
		virtual bool Load([[maybe_unused]] TESFile* a_file) { return true; }																																						 // 09
		virtual bool LoadPartial([[maybe_unused]] TESFile* a_file) { return true; }																																					 // 0A
		virtual bool LoadEdit(TESFile* a_file) { return Load(a_file); }																																								 // 0B
		virtual TESForm* CreateDuplicateForm(bool a_createEditorID, BSTHashMap<TESForm*, TESForm*>* a_copyMap);																														 // 0C
		virtual bool AddChange(CHANGE_TYPE a_changeFlags);																																											 // 0D
		virtual void RemoveChange(CHANGE_TYPE a_changeFlags);																																										 // 0E
		virtual bool FindInFileFast([[maybe_unused]] TESFile* a_file) { return false; }																																				 // 0F
		virtual bool CheckSaveGame([[maybe_unused]] BGSSaveFormBuffer* a_saveGameBuffer) const { return true; }																														 // 10
		virtual void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer);																																									 // 11
		virtual void LoadGame(BGSLoadFormBuffer* a_loadGameBuffer);																																									 // 12
		virtual void InitLoadGame([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) { return; }																																	 // 13
		virtual void FinishLoadGame([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) { return; }																																 // 14
		virtual void Revert([[maybe_unused]] BGSLoadFormBuffer* a_loadGameBuffer) { return; }																																		 // 15
		virtual void InitItemImpl() { return; }																																														 // 16
		virtual TESFile* GetRevertFile() const;																																														 // 17
		virtual TESFile* GetDescriptionOwnerFile() const;																																											 // 18
		virtual ENUM_FORMTYPE GetSavedFormType() const { return *formType; }																																						 // 19
		virtual void GetFormDetailedString(char* a_dest, std::uint32_t a_size) const;																																				 // 1A
		virtual bool GetKnown() const { return formFlags & FORM_FLAGS::kKnown; }																																					 // 1B
		virtual bool GetRandomAnim() const { return formFlags & FORM_FLAGS::kRandomAnim; }																																			 // 1C
		virtual bool GetPlayable([[maybe_unused]] const TBO_InstanceData* a_data) const { return formFlags & FORM_FLAGS::kPlayable; }																								 // 1D
		virtual bool IsHeadingMarker() const { return false; }																																										 // 1E
		virtual bool IsHeadtrackMarker() const { return false; }																																									 // 1F
		virtual bool GetDangerous() const { return formFlags & FORM_FLAGS::kDangerous; }																																			 // 20
		virtual bool QHasCurrents() const { return formFlags & FORM_FLAGS::kHasCurrents; }																																			 // 21
		virtual bool GetObstacle() const { return formFlags & FORM_FLAGS::kObstacle; }																																				 // 22
		virtual bool QIsLODLandObject() const { return false; }																																										 // 23
		virtual bool GetOnLocalMap() const { return formFlags & FORM_FLAGS::kOnLocalMap; }																																			 // 24
		virtual bool GetMustUpdate() const { return formFlags & FORM_FLAGS::kMustUpdate; }																																			 // 25
		virtual void SetOnLocalMap(bool a_val);																																														 // 26
		virtual bool GetIgnoredBySandbox() const { return false; }																																									 // 27
		virtual void SetDelete(bool a_deleted);																																														 // 28
		virtual void SetAltered(bool a_altered);																																													 // 29
		virtual void SaveObjectBound() { return; }																																													 // 2A
		virtual void LoadObjectBound([[maybe_unused]] TESFile* a_file) { return; }																																					 // 2B
		virtual void SavePreviewTransform(CHUNK_ID) { return; }																																										 // 2C
		virtual void LoadPreviewTransform([[maybe_unused]] TESFile* a_file) { return; }																																				 // 2D
		virtual bool IsBoundObject() const { return false; }																																										 // 2E
		virtual bool IsObject() const { return false; }																																												 // 2F
		virtual bool IsMagicItem() const { return false; }																																											 // 30
		virtual bool IsWater() const { return false; }																																												 // 31
		virtual TESObjectREFR* IsReference() { return nullptr; }																																									 // 33
		virtual const TESObjectREFR* IsReference() const { return nullptr; }																																						 // 32
		virtual std::uint32_t GetRefCount() const { return 0; }																																										 // 34
		virtual const char* GetTextForParsedSubTag(const BSFixedString& a_subTag) const;																																			 // 35
		virtual void Copy([[maybe_unused]] TESForm* a_copy) { return; }																																								 // 36
		virtual bool BelongsInGroup(FORM* a_groupFORM, bool a_allowParentGroups, bool a_currentOnly);																																 // 37
		virtual void CreateGroupData(FORM* a_outGroupFORM, FORM_GROUP* a_parentGroup);																																				 // 38
		virtual std::uint32_t GetFormEditorIDLength() const;																																										 // 39
		virtual const char* GetFormEditorID() const { return ""; }																																									 // 3A
		virtual bool SetFormEditorID([[maybe_unused]] const char* a_editorID) { return true; }																																		 // 3B
		virtual bool IsParentForm() { return false; }																																												 // 3C
		virtual bool IsParentFormTree() { return false; }																																											 // 3D
		virtual bool IsFormTypeChild([[maybe_unused]] std::uint8_t a_type) { return false; }																																		 // 3E
		virtual bool LoopingActivate(TESObjectREFR* a_itemActivated, TESObjectREFR* a_actionRef) { return Activate(a_itemActivated, a_actionRef, nullptr, 1); }																		 // 3F
		virtual bool Activate([[maybe_unused]] TESObjectREFR* a_itemActivated, [[maybe_unused]] TESObjectREFR* a_actionRef, [[maybe_unused]] TESBoundObject* a_objectToGet, [[maybe_unused]] std::int32_t a_count) { return false; } // 40
		virtual void SetFormID(TESFormID a_formID, bool a_updateFile);																																								 // 41
		virtual const char* GetObjectTypeName() const { return ""; }																																								 // 42
		virtual bool QAvailableInGame() const { return true; }																																										 // 43
		virtual BGSMod::Template::Items* GetObjectTemplate() { return nullptr; }																																					 // 44
		virtual BGSPreviewTransform* GetPreviewTransform() { return nullptr; }																																						 // 45
		virtual BGSSoundTagComponent* GetSoundTagComponent() { return nullptr; }																																					 // 46
		virtual std::uint32_t GetFilledSlots() const;																																												 // 47
		virtual std::uint32_t GetFilledSlotsImpl() const { return static_cast<std::uint32_t>(-1); }																																	 // 48
		virtual float GetDesirability([[maybe_unused]] TBO_InstanceData* a_instanceData, [[maybe_unused]] const TESForm* a_user) const { return 0.0F; }																				 // 49

		static void AddCompileIndex(std::uint32_t& a_id, TESFile* a_file)
		{
			using func_t = decltype(&TESForm::AddCompileIndex);
			static REL::Relocation<func_t> func{ REL::RelocationID(1315637, 2193152) };
			return func(a_id, a_file);
		}

		[[nodiscard]] static auto GetAllForms()
			-> std::pair<
				BSTHashMap<std::uint32_t, TESForm*>*,
				std::reference_wrapper<BSReadWriteLock>>
		{
			static REL::Relocation<BSTHashMap<std::uint32_t, TESForm*>**> allForms{ REL::RelocationID(422985, 2689178) };
			static REL::Relocation<BSReadWriteLock*> allFormsMapLock{ REL::RelocationID(691815, 2689189) };
			return { *allForms, *allFormsMapLock };
		}

		[[nodiscard]] static auto GetAllFormsByEditorID()
			-> std::pair<
				BSTHashMap<BSFixedString, TESForm*>*,
				std::reference_wrapper<BSReadWriteLock>>
		{
			static REL::Relocation<BSTHashMap<BSFixedString, TESForm*>**> allFormsByEditorID{ REL::RelocationID(642758, 2689179) };
			static REL::Relocation<BSReadWriteLock*> allFormsEditorIDMapLock{ REL::RelocationID(910917, 2689190) };
			return { *allFormsByEditorID, *allFormsEditorIDMapLock };
		}

		[[nodiscard]] TESFile* GetFile(std::int32_t a_index = -1) const
		{
			using func_t = decltype(&TESForm::GetFile);
			static REL::Relocation<func_t> func{ REL::RelocationID(1376557, 2193103) };
			return func(this, a_index);
		}

		[[nodiscard]] static TESForm* GetFormByID(TESFormID a_formID);

		template <
			class T,
			class = std::enable_if_t<
				std::negation_v<
					std::disjunction<
						std::is_pointer<T>,
						std::is_reference<T>,
						std::is_const<T>,
						std::is_volatile<T>>>>>
		[[nodiscard]] static T* GetFormByID(TESFormID a_formID)
		{
			const auto form = GetFormByID(a_formID);
			return form ? form->As<T>() : nullptr;
		}

		[[nodiscard]] static TESForm* GetFormByEditorID(const BSFixedString& a_editorID);

		template <
			class T,
			class = std::enable_if_t<
				std::negation_v<
					std::disjunction<
						std::is_pointer<T>,
						std::is_reference<T>,
						std::is_const<T>,
						std::is_volatile<T>>>>>
		[[nodiscard]] static T* GetFormByEditorID(const BSFixedString& a_editorID)
		{
			const auto form = GetFormByEditorID(a_editorID);
			return form ? form->As<T>() : nullptr;
		}

		[[nodiscard]] static std::span<FORM_ENUM_STRING, 159> GetFormEnumString()
		{
			static REL::Relocation<FORM_ENUM_STRING(*)[159]> functions{ REL::RelocationID(1309967, 1309967) };
			return { *functions };
		}

		[[nodiscard]] static ENUM_FORMTYPE GetFormTypeFromString(const char* a_formTypeString)
		{
			using func_t = decltype(&TESForm::GetFormTypeFromString);
			static REL::Relocation<func_t> func{ REL::RelocationID(565203, 2193108) };
			return func(a_formTypeString);
		}

		[[nodiscard]] static const char* GetFormTypeString(ENUM_FORMTYPE a_formType)
		{
			const auto formTypes = GetFormEnumString();
			const auto index = std::to_underlying(a_formType);

			if (index < 0 || index >= formTypes.size()) {
				return "";
			}

			return formTypes[index].formString;
		}

		[[nodiscard]] const char* GetFormTypeString() const
		{
			return GetFormTypeString(GetFormType());
		}

		[[nodiscard]] bool Is(ENUM_FORMTYPE a_type) const noexcept { return GetFormType() == a_type; }

		template <class... Args>
		[[nodiscard]] bool Is(Args... a_args) const noexcept //
			requires(std::same_as<Args, ENUM_FORMTYPE> && ...)
		{
			return (Is(a_args) || ...);
		}

		template <class T>
		[[nodiscard]] bool Is() const noexcept //
			requires(std::derived_from<T, TESForm> &&
					 !std::is_pointer_v<T> &&
					 !std::is_reference_v<T>)
		{
			return Is(T::FORMTYPE);
		}

		[[nodiscard]] bool IsNot(ENUM_FORMTYPE a_type) const noexcept { return !Is(a_type); }
		template <class... Args>

		[[nodiscard]] bool IsNot(Args... a_args) const noexcept //
			requires(std::same_as<Args, ENUM_FORMTYPE> && ...)
		{
			return (IsNot(a_args) && ...);
		}

		template <
			class T,
			class = std::enable_if_t<
				std::negation_v<
					std::disjunction<
						std::is_pointer<T>,
						std::is_reference<T>,
						std::is_const<T>,
						std::is_volatile<T>>>>>
		[[nodiscard]] T* As() noexcept;

		template <
			class T,
			class = std::enable_if_t<
				std::negation_v<
					std::disjunction<
						std::is_pointer<T>,
						std::is_reference<T>,
						std::is_const<T>,
						std::is_volatile<T>>>>>
		[[nodiscard]] const T* As() const noexcept;

		[[nodiscard]] std::uint32_t GetFormFlags() const noexcept { return formFlags; }
		[[nodiscard]] TESFormID GetFormID() const noexcept { return formID; }
		[[nodiscard]] ENUM_FORMTYPE GetFormType() const noexcept { return *formType; }
		[[nodiscard]] TESFormID GetLocalFormID() const;

		[[nodiscard]] bool IsAlchemyItem() const noexcept { return Is(ENUM_FORMTYPE::kALCH); }
		[[nodiscard]] bool IsCreated() const noexcept { return (formID >> (8 * 3)) == 0xFF; }
		[[nodiscard]] bool IsDeleted() noexcept { return formFlags & FORM_FLAGS::kDeleted; }
		[[nodiscard]] bool IsDisabled() noexcept { return formFlags & FORM_FLAGS::kDisabled; }
		[[nodiscard]] bool IsInitialized() const noexcept { return formFlags & FORM_FLAGS::kInitialized; }

		[[nodiscard]] bool IsPlayer() const noexcept { return GetFormID() == 0x00000007; }
		[[nodiscard]] bool IsPlayerRef() const noexcept { return GetFormID() == 0x00000014; }
		[[nodiscard]] bool IsWeapon() const noexcept { return Is(ENUM_FORMTYPE::kWEAP); }

		void SetInGameFormFlags(InGameFormFlags a_flags, bool a_set)
		{
			if (a_set) {
				inGameFormFlags.set(a_flags);
				AddChange(CHANGE_TYPE::kFormFlags);
			}
			else {
				inGameFormFlags.reset(a_flags);
				AddChange(CHANGE_TYPE::kFormFlags);
			}
		}

		void SetTemporary()
		{
			using func_t = decltype(&TESForm::SetTemporary);
			static REL::Relocation<func_t> func{ REL::RelocationID(482454, 2193125) };
			return func(this);
		}

		// members
		TESFileContainer sourceFiles;								  // 08
		std::uint32_t formFlags;									  // 10
		TESFormID formID;											  // 14
		REX::EnumSet<InGameFormFlags, std::uint16_t> inGameFormFlags; // 18
		REX::Enum<ENUM_FORMTYPE, std::uint8_t> formType;			  // 1A
	};
	static_assert(sizeof(TESForm) == 0x20);

	class __declspec(novtable) BGSKeyword
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSKeyword };
		inline static constexpr auto VTABLE{ VTABLE::BGSKeyword };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kKYWD };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kRestricted = 1 << 15
			};
		};

		[[nodiscard]] static uint16_t GetIndexForTypedKeyword(const BGSKeyword* a_keyword, KeywordType a_type);
		[[nodiscard]] static BGSKeyword* GetTypedKeywordByIndex(KeywordType a_type, std::uint16_t a_index);
		[[nodiscard]] static auto GetTypedKeywords() -> std::optional<std::span<BSTArray<BGSKeyword*>, std::to_underlying(KeywordType::kTotal)>>;

		// members
		BSFixedString formEditorID; // 20
	};
	static_assert(sizeof(BGSKeyword) == 0x28);

	class __declspec(novtable) BGSLocationRefType
		: public BGSKeyword // 00
	{
	public:
		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		inline static constexpr auto RTTI{ RTTI::BGSLocationRefType };
		inline static constexpr auto VTABLE{ VTABLE::BGSLocationRefType };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kLCRT };
	};
	static_assert(sizeof(BGSLocationRefType) == 0x28);

	class __declspec(novtable) BGSAction
		: public BGSKeyword // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAction };
		inline static constexpr auto VTABLE{ VTABLE::BGSAction };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kAACT };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kRestricted = 1 << 15
			};
		};

		// members
		std::uint32_t index; // 28
	};
	static_assert(sizeof(BGSAction) == 0x30);

	class __declspec(novtable) BGSTransform
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSTransform };
		inline static constexpr auto VTABLE{ VTABLE::BGSTransform };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kTRNS };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kAroundOrigin = 1 << 16
			};
		};

		struct TransformData
		{
		public:
			// members
			NiPoint3 position; // 00
			NiPoint3 rotation; // 0C
			float scale;	   // 18
			float minZoom;	   // 1C
			float maxZoom;	   // 20
		};
		static_assert(sizeof(TransformData) == 0x24);

		// members
		TransformData data; // 20
	};
	static_assert(sizeof(BGSTransform) == 0x48);

	class __declspec(novtable) BGSMenuIcon
		: public TESForm, // 00
		  public TESIcon  // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMenuIcon };
		inline static constexpr auto VTABLE{ VTABLE::BGSMenuIcon };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kMICN };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
	};
	static_assert(sizeof(BGSMenuIcon) == 0x30);

	class __declspec(novtable) TESGlobal
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESGlobal };
		inline static constexpr auto VTABLE{ VTABLE::TESGlobal };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kGLOB };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kConstant = 1 << 6,
				kIgnored = 1 << 12
			};
		};

		[[nodiscard]] float GetValue() const noexcept { return value; }
		void SetValue(float a_value) noexcept { value = a_value; }

		// members
		BSString formEditorID; // 20
		float value;		   // 30
	};
	static_assert(sizeof(TESGlobal) == 0x38);

	class __declspec(novtable) BGSDamageType
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSDamageType };
		inline static constexpr auto VTABLE{ VTABLE::BGSDamageType };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kDMGT };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct Data
		{
		public:
			// members
			ActorValueInfo* resistance; // 00
			MagicItem* spell;			// 08
		};
		static_assert(sizeof(Data) == 0x10);

		// members
		Data data; // 20
	};
	static_assert(sizeof(BGSDamageType) == 0x30);

	struct CLASS_DATA
	{
	public:
		// members
		std::uint32_t serviceFlags; // 00
		float bleedoutDefault;		// 04
	};
	static_assert(sizeof(CLASS_DATA) == 0x8);

	class __declspec(novtable) TESClass
		: public TESForm,		  // 00
		  public TESFullName,	  // 20
		  public TESDescription,  // 30
		  public TESTexture,	  // 48
		  public BGSPropertySheet // 58
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESClass };
		inline static constexpr auto VTABLE{ VTABLE::TESClass };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kCLAS };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		CLASS_DATA data; // 68
	};
	static_assert(sizeof(TESClass) == 0x70);

	class __declspec(novtable) TESEyes
		: public TESForm,	  // 00
		  public TESFullName, // 20
		  public TESTexture	  // 30
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESEyes };
		inline static constexpr auto VTABLE{ VTABLE::TESEyes };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kEYES };

		enum class Flags
		{
			kNone = 0,
			kPlayable = 1 << 0,
			kNotMale = 1 << 1,
			kNotFemale = 1 << 2
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kNonPlayable = 1 << 2,
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> flags; // 40
	};
	static_assert(sizeof(TESEyes) == 0x48);

	class __declspec(novtable) EffectSetting
		: public TESForm,			   // 000
		  public TESFullName,		   // 020
		  public BGSMenuDisplayObject, // 030
		  public BGSKeywordForm		   // 040
	{
	public:
		inline static constexpr auto RTTI{ RTTI::EffectSetting };
		inline static constexpr auto VTABLE{ VTABLE::EffectSetting };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kMGEF };

		using FilterValidationFunction_t = bool(EffectSetting*, void*);

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct EffectSettingData
		{
		public:
			enum class Flags
			{
				kNone = 0,
				kHostile = 1 << 0,
				kRecover = 1 << 1,
				kDetrimental = 1 << 2,
				kSnapToNavMesh = 1 << 3,
				kNoHitEvent = 1 << 4,
				kDispelWithKeywords = 1 << 8,
				kNoDuration = 1 << 9,
				kNoMagnitude = 1 << 10,
				kNoArea = 1 << 11,
				kFXPersist = 1 << 12,
				kGoryVisuals = 1 << 14,
				kHideInUI = 1 << 15,
				kNoRecast = 1 << 17,
				kPowerAffectsMagnitude = 1 << 21,
				kPowerAffectsDuration = 1 << 22,
				kPainless = 1 << 26,
				kNoHitEffect = 1 << 27,
				kNoDeathDispel = 1 << 28
			};

			// members
			REX::EnumSet<Flags, std::uint32_t> flags;						  // 000
			float baseCost;													  // 004
			TESForm* associatedForm;										  // 008
			ActorValueInfo* associatedSkill;								  // 010
			ActorValueInfo* resistVariable;									  // 018
			std::int16_t numCounterEffects;									  // 020
			TESObjectLIGH* light;											  // 028
			float taperWeight;												  // 030
			TESEffectShader* effectShader;									  // 038
			TESEffectShader* enchantEffect;									  // 040
			std::int32_t minimumSkill;										  // 048
			std::int32_t spellmakingArea;									  // 04C
			float spellmakingChargeTime;									  // 050
			float taperCurve;												  // 054
			float taperDuration;											  // 058
			float secondaryAVWeight;										  // 05C
			REX::Enum<EffectArchetypes::ArchetypeID, std::int32_t> archetype; // 060
			ActorValueInfo* primaryAV;										  // 068
			BGSProjectile* projectileBase;									  // 070
			BGSExplosion* explosion;										  // 078
			REX::Enum<MagicSystem::CastingType, std::uint32_t> castingType;	  // 080
			REX::Enum<MagicSystem::Delivery, std::uint32_t> delivery;		  // 084
			ActorValueInfo* secondaryAV;									  // 088
			BGSArtObject* castingArt;										  // 090
			BGSArtObject* hitEffectArt;										  // 098
			BGSImpactDataSet* impactDataSet;								  // 0A0
			float skillUsageMult;											  // 0A8
			BGSDualCastData* dualCastData;									  // 0B0
			float dualCastScale;											  // 0B8
			BGSArtObject* enchantEffectArt;									  // 0C0
			BGSReferenceEffect* hitVisuals;									  // 0C8
			BGSReferenceEffect* enchantVisuals;								  // 0D0
			SpellItem* equipAbility;										  // 0D8
			TESImageSpaceModifier* imageSpaceMod;							  // 0E0
			BGSPerk* perk;													  // 0E8
			REX::Enum<SOUND_LEVEL, std::uint32_t> castingSoundLevel;		  // 0F0
			float aiScore;													  // 0F4
			float aiDelayTime;												  // 0F8
		};
		static_assert(sizeof(EffectSettingData) == 0x100);

		struct SoundPair
		{
		public:
			// members
			REX::Enum<MagicSystem::SoundID, std::uint32_t> id; // 00
			BGSSoundDescriptorForm* sound;					   // 08
		};
		static_assert(sizeof(SoundPair) == 0x10);

		// members
		FilterValidationFunction_t* filterValidationFunction; // 060
		void* filterValidationItem;							  // 068
		EffectSettingData data;								  // 070
		BSSimpleList<EffectSetting*> counterEffects;		  // 170
		BSTArray<EffectSetting::SoundPair> effectSounds;	  // 180
		BGSLocalizedString magicItemDescription;			  // 198
		std::int32_t effectLoadedCount;						  // 1A0
		std::int32_t associatedItemLoadedCount;				  // 1A4
		TESCondition conditions;							  // 1A8
	};
	static_assert(sizeof(EffectSetting) == 0x1B0);

	struct TEXTURE_HAVOK_DATA
	{
	public:
		// members
		std::int8_t friction;	 // 00
		std::int8_t restitution; // 01
	};
	static_assert(sizeof(TEXTURE_HAVOK_DATA) == 0x2);

	class __declspec(novtable) TESLandTexture
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESLandTexture };
		inline static constexpr auto VTABLE{ VTABLE::TESLandTexture };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kLTEX };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BGSTextureSet* textureSet;				  // 20
		TEXTURE_HAVOK_DATA havokData;			  // 28
		BGSMaterialType* materialType;			  // 30
		std::int8_t specularExponent;			  // 38
		std::int32_t shaderTextureIndex;		  // 3C
		BSSimpleList<TESGrass*> textureGrassList; // 40
	};
	static_assert(sizeof(TESLandTexture) == 0x50);

	class __declspec(novtable) TESWeather
		: public TESForm // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESWeather };
		inline static constexpr auto VTABLE{ VTABLE::TESWeather };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kWTHR };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		enum class SpellContext
		{
			kApplyOnLightning,
			kApplyWhenActive
		};

		enum class SoundType
		{
			kDefault,
			kPrecipitation,
			kWind,
			kThunder
		};

		struct SpellData
		{
		public:
			// members
			MagicItem* spell; // 00
			float threshold;  // 08
		};
		static_assert(sizeof(SpellData) == 0x10);

		struct WeatherSound
		{
		public:
			// members
			BGSSoundDescriptorForm* soundForm;		  // 00
			REX::Enum<SoundType, std::uint32_t> type; // 08
		};
		static_assert(sizeof(WeatherSound) == 0x10);

		struct WeatherSoundList
			: public BSSimpleList<WeatherSound*>
		{
		public:
		};
		static_assert(sizeof(WeatherSoundList) == 0x10);

		// members
		REX::Enum<SpellContext, std::uint32_t> context;							 // 020
		TESTexture1024 cloudTexture[32];										 // 028
		std::int8_t cloudLayerSpeedY[32];										 // 228
		std::int8_t cloudLayerSpeedX[32];										 // 248
		std::uint32_t cloudColorData[32][8];									 // 268
		float cloudAlpha[32][8];												 // 668
		std::uint32_t cloudLayerDisabledBits;									 // A68
		std::int8_t weatherData[20];											 // A6C
		float fogData[18];														 // A80
		std::uint32_t colorData[19][8];											 // AC8
		float fogColorScales[4][8];												 // D28
		SpellData weatherSpellData[2];											 // DA8
		WeatherSoundList soundList;												 // DC8
		BSTArray<TESObjectSTAT*> skyStatics;									 // DD8
		std::uint32_t numCloudLayers;											 // DF0
		TESImageSpace* imageSpace[8];											 // DF8
		BGSGodRays* godRays[8];													 // E38
		BGSDirectionalAmbientLightingColors directionalAmbientLightingColors[8]; // E78
		TESModel aurora;														 // F78
		BGSLensFlare* sunGlareLensFlare;										 // FA8
		float volatilityMult;													 // FB0
		float visibilityMult;													 // FB4
		BGSShaderParticleGeometryData* precipitationData;						 // FB8
		BGSReferenceEffect* referenceEffect;									 // FC0
	};
	static_assert(sizeof(TESWeather) == 0xFC8);

	struct WeatherEntry
	{
	public:
		// members
		TESWeather* weather;  // 00
		std::uint32_t chance; // 08
		TESGlobal* chanceVar; // 10
	};
	static_assert(sizeof(WeatherEntry) == 0x18);

	class TESWeatherList : BSSimpleList<WeatherEntry*>
	{
	public:
	};
	static_assert(sizeof(TESWeatherList) == 0x10);

	class __declspec(novtable) TESClimate
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESClimate };
		inline static constexpr auto VTABLE{ VTABLE::TESClimate };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kCLMT };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		TESModel nightSky;			// 20
		TESWeatherList weatherList; // 50
		TESTexture skyObjects[2];	// 60
		std::int8_t data[6];		// 80
	};
	static_assert(sizeof(TESClimate) == 0x88);

	class __declspec(novtable) BGSShaderParticleGeometryData
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSShaderParticleGeometryData };
		inline static constexpr auto VTABLE{ VTABLE::BGSShaderParticleGeometryData };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kSPGD };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BSTArray<SETTING_VALUE> data; // 20
		TESTexture particleTexture;	  // 38
		BSFixedString materialName;	  // 48
	};
	static_assert(sizeof(BGSShaderParticleGeometryData) == 0x50);

	class __declspec(novtable) BGSReferenceEffect
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSReferenceEffect };
		inline static constexpr auto VTABLE{ VTABLE::BGSReferenceEffect };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kRFCT };

		enum class Flags
		{
			kNone = 0,
			kFaceTarget = 1 << 0,
			kAttachToCamera = 1 << 1,
			kInheritRotation = 1 << 2
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct Data
		{
		public:
			// members
			BGSArtObject* artObject;				  // 00
			TESEffectShader* effectShader;			  // 08
			REX::EnumSet<Flags, std::uint32_t> flags; // 10
		};
		static_assert(sizeof(Data) == 0x18);

		// members
		Data data; // 20
	};
	static_assert(sizeof(BGSReferenceEffect) == 0x38);

	class __declspec(novtable) TESRegion
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESRegion };
		inline static constexpr auto VTABLE{ VTABLE::TESRegion };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kREGN };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kBorderRegion = 1 << 6,
				kIgnored = 1 << 12
			};
		};

		// add
		virtual bool Validate(); // 49

		// members
		TESRegionDataList* dataList;				   // 20
		BSSimpleList<TESRegionPointList*>* pointLists; // 28
		TESWorldSpace* worldSpace;					   // 30
		TESWeather* currentWeather;					   // 38
		NiColor emittanceColor;						   // 40
		float lodDistanceModifier;					   // 4C
		float occlusionAccuracy;					   // 50
	};
	static_assert(sizeof(TESRegion) == 0x58);

	struct EXTERIOR_DATA // XCLC
	{
	public:
		// members
		std::int32_t cellX;	 // 04
		std::int32_t cellY;	 // 08
		std::uint64_t unk08; // 10
		std::uint64_t unk10; // 18
		std::uint32_t unk18; // 1C
		NiPoint2 worldPos;	 // 20
	};

	class NavMeshArray
	{
	public:
		// members
		BSTArray<BSTSmartPointer<NavMesh>> navMeshes; // 00
	};
	static_assert(sizeof(NavMeshArray) == 0x18);

	struct LOADED_CELL_DATA
	{
	public:
		struct AnimatedRefObject
		{
		public:
			// members
			ObjectRefHandle handle;		// 00
			std::int32_t numSkipFrames; // 04
		};
		static_assert(sizeof(AnimatedRefObject) == 0x8);

		// members
		BSTHashMap<ObjectRefHandle, TESForm*> emittanceSourceRefMap;			   // 000
		BSTHashMap<ObjectRefHandle, NiNode*> emittanceLightRefMap;				   // 030
		BSTHashMap<ObjectRefHandle, NiPointer<BSMultiBoundNode>> multiboundRefMap; // 060
		BSTHashMap<BSMultiBoundNode*, ObjectRefHandle> refMultiboundMap;		   // 090
		BSTArray<NiPointer<NiNode>> preCombined;								   // 0C0
		BSTArray<NiPointer<NiNode>> attachedTransitionCells;					   // 0D8
		BSTArray<AnimatedRefObject> animatedRefs;								   // 0F0
		BSTArray<ObjectRefHandle> flickeringLights;								   // 108
		BSTArray<ObjectRefHandle> movingRefs;									   // 120
		BSTArray<ObjectRefHandle> decalRefs;									   // 138
		BSTArray<ObjectRefHandle> skyActors;									   // 150
		BSTArray<ObjectRefHandle> flightAvoidAreas;								   // 168
		mutable BSReadWriteLock waterLock;										   // 180
		void* combinedGeometry;													   // 188 - To-Do
		NiPointer<QueuedFile> combinedGeometryTask;								   // 190
		BSSimpleList<ObjectRefHandle> activatingRefs;							   // 198
		BSSimpleList<ObjectRefHandle> waterRefs;								   // 1A8
		NiPointer<BSPortalGraph> portalGraph;									   // 1B8
		NiPointer<NiNode> cell3D;												   // 1C0
		NiPointer<NiNode> lightMarkerNode;										   // 1C8
		NiPointer<NiNode> soundMarkerNode;										   // 1D0
		NiPointer<NiNode> multiBoundNode;										   // 1D8
		NiPointer<NiNode> combinedObjects;										   // 1E0
		NiPointer<NiNode> combinedStaticCollision;								   // 1E8
		BGSEncounterZone* encounterZone;										   // 1F0
		std::size_t visibleDistantFadeInTime;									   // 1F8
		std::int32_t criticalQueuedRefCount;									   // 200
		std::int32_t queuedRefCount;											   // 204
		std::int32_t queuedDistantRefCount;										   // 208
		std::uint32_t refsAttachedDelay;										   // 20C
		BSTAtomicValue<std::uint32_t> combinedObjectsAttached;					   // 210
		bool decalsQueued;														   // 214
		bool refsFullyLoaded;													   // 215
		bool combinedObjectsRegistered;											   // 216
		bool grassIsShown;														   // 217
	};
	static_assert(sizeof(LOADED_CELL_DATA) == 0x218);

	class __declspec(novtable) TESObjectCELL
		: public TESForm,	 // 00
		  public TESFullName // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectCELL };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectCELL };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kCELL };

		enum class Flags
		{
			kNone = 0,
			kIsInterior = 1 << 0,
			kHasWater = 1 << 1,
			kCanTravelFromHere = 1 << 2,
			kNoLODWater = 1 << 3,
			kHasTempData = 1 << 4,
			kPublicArea = 1 << 5,
			kHandChanged = 1 << 6,
			kShowSky = 1 << 7,
			kUseSkyLighting = 1 << 8,
			kWarnToLeave = 1 << 9,
			kHiddenFromInteriorList = 1 << 10,
			kSunlightShadows = 1 << 11,
			kDistantLODOnly = 1 << 12,
			kFollowersCannotTravelHere = 1 << 13
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kNoPreVis = 1 << 7,
				kPersistent = 1 << 10,
				kIgnored = 1 << 12,
				kOffLimits = 1 << 17,
				kCompressed = 1 << 18,
				kCannotWait = 1 << 19
			};
		};

		enum class CELL_STATE
		{
			kNotLoaded,
			kUnloading,
			kLoadingData,
			kLoading,
			kLoaded,
			kDetaching,
			kAttachQueued,
			kAttaching,
			kAttached
		};

		[[nodiscard]] bhkWorld* GetbhkWorld() const
		{
			using func_t = decltype(&TESObjectCELL::GetbhkWorld);
			static REL::Relocation<func_t> func{ REL::ID(1326073) };
			return func(this);
		}

		[[nodiscard]] bool GetCantWaitHere()
		{
			using func_t = decltype(&TESObjectCELL::GetCantWaitHere);
			static REL::Relocation<func_t> func{ REL::RelocationID(376940, 2200287) };
			return func(this);
		}

		[[nodiscard]] std::int32_t GetDataX()
		{
			using func_t = decltype(&TESObjectCELL::GetDataX);
			static REL::Relocation<func_t> func{ REL::RelocationID(445210, 2200213) };
			return func(this);
		}

		[[nodiscard]] std::int32_t GetDataY()
		{
			using func_t = decltype(&TESObjectCELL::GetDataY);
			static REL::Relocation<func_t> func{ REL::RelocationID(1322816, 2200214) };
			return func(this);
		}

		[[nodiscard]] BGSEncounterZone* GetEncounterZone() const
		{
			using func_t = decltype(&TESObjectCELL::GetEncounterZone);
			static REL::Relocation<func_t> func{ REL::RelocationID(1414637, 2200242) };
			return func(this);
		}

		[[nodiscard]] BGSLocation* GetLocation() const
		{
			using func_t = decltype(&TESObjectCELL::GetLocation);
			static REL::Relocation<func_t> func{ REL::RelocationID(868663, 2200179) };
			return func(this);
		}

		[[nodiscard]] TESForm* GetOwner()
		{
			using func_t = decltype(&TESObjectCELL::GetOwner);
			static REL::Relocation<func_t> func{ REL::ID(910422) };
			return func(this);
		}

		[[nodiscard]] TESRegionList* GetRegionList(bool a_createIfMissing)
		{
			using func_t = decltype(&TESObjectCELL::GetRegionList);
			static REL::Relocation<func_t> func{ REL::RelocationID(1565031, 2200265) };
			return func(this, a_createIfMissing);
		}

		[[nodiscard]] NiAVObject* Pick(bhkPickData& pd)
		{
			using func_t = decltype(&TESObjectCELL::Pick);
			static REL::Relocation<func_t> func{ REL::ID(434717) };
			return func(this, pd);
		}

		BSContainer::ForEachResult ForEachRef(std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback) const;
		BSContainer::ForEachResult ForEachRefInRange(const NiPoint3& a_origin, float a_radius, std::function<BSContainer::ForEachResult(TESObjectREFR*)> a_callback) const;

		[[nodiscard]] bool HasWater() const noexcept { return cellFlags.any(Flags::kHasWater); }
		[[nodiscard]] bool IsExterior() const noexcept { return !IsInterior(); }
		[[nodiscard]] bool IsInterior() const noexcept { return cellFlags.any(Flags::kIsInterior); }
		[[nodiscard]] bool IsAttached() const noexcept { return cellState == CELL_STATE::kAttached; }

		[[nodiscard]] TESWaterForm* GetWaterType() const noexcept;
		[[nodiscard]] EXTERIOR_DATA* GetExteriorData() const noexcept { return IsExterior() ? cellDataExterior : nullptr; }
		[[nodiscard]] INTERIOR_DATA* GetInteriorData() const noexcept { return IsInterior() ? cellDataInterior : nullptr; }

		// members
		mutable BSSpinLock grassCreateLock;				  // 30
		mutable BSSpinLock grassTaskLock;				  // 38
		REX::EnumSet<Flags, std::uint16_t> cellFlags;	  // 40
		std::uint16_t cellGameFlags;					  // 42
		REX::EnumSet<CELL_STATE, std::uint8_t> cellState; // 44
		bool autoWaterLoaded;							  // 45
		bool cellDetached;								  // 46
		BSTSmartPointer<ExtraDataList> extraList;		  // 48
		union
		{
			EXTERIOR_DATA* cellDataExterior;
			INTERIOR_DATA* cellDataInterior;
		}; // 50
		TESObjectLAND* cellLand;													 // 58
		float waterHeight;															 // 60
		NavMeshArray* navMeshes;													 // 68
		BSTArray<NiPointer<TESObjectREFR>> references;								 // 70
		BSTSmartPointer<BGSWaterCollisionManager::AutoWater> autoWater;				 // 77
		BSTSet<BSTSmartPointer<BGSWaterCollisionManager::BGSWaterUpdateI>> waterSet; // 80
		mutable BSSpinLock spinLock;												 // C0
		union
		{
			TESWorldSpace* worldSpace;
			std::uint32_t tempDataOffset;
		}; // C8
		LOADED_CELL_DATA* loadedData;		   // D0
		BGSLightingTemplate* lightingTemplate; // D8
		void* visibilityData;				   // E0 - To-Do
		std::uint32_t rootVisibilityCellID;	   // E8
		std::uint16_t visCalcDate;			   // EC
		std::uint16_t preCombineDate;		   // F0
	};
	static_assert(sizeof(TESObjectCELL) == 0xF0);

	struct OBJ_LAND
	{
	public:
		enum class LAND
		{
			kHeightAltered = 1 << 0,
			kCLRAltered = 1 << 1,
			kTexAltered = 1 << 2,
			kLoaded = 1 << 3,
			kGoodNormals = 1 << 4,
			kHiResHeightfield = 1 << 5,

			kRemapped = 1 << 10,

			kDataAltered = kHeightAltered | kCLRAltered | kTexAltered | kHiResHeightfield,
		};

		// members
		REX::EnumSet<LAND, std::uint32_t> flags; // 00
	};
	static_assert(sizeof(OBJ_LAND) == 0x4);

	class __declspec(novtable) TESObjectLAND
		: public TESForm,	  // 00
		  public TESChildCell // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectLAND };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectLAND };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kLAND };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kCompressed = 1 << 18
			};
		};

		struct LoadedLandData;

		// members
		OBJ_LAND data;						  // 28
		TESObjectCELL* parentCell;			  // 30
		NiPointer<QueuedFile> queuedTextures; // 38
		LoadedLandData* loadedData;			  // 40
	};
	static_assert(sizeof(TESObjectLAND) == 0x48);

	struct DIALOGUE_DATA
	{
	public:
		// members
		std::int8_t flags;	   // 00
		std::int8_t type;	   // 01
		std::uint16_t subtype; // 02
	};
	static_assert(sizeof(DIALOGUE_DATA) == 0x4);

	class __declspec(novtable) TESTopic
		: public TESForm,	 // 00
		  public TESFullName // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESTopic };
		inline static constexpr auto VTABLE{ VTABLE::TESTopic };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kDIAL };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kPartialForm = 1 << 14
			};
		};

		struct InfoTree;

		// members
		DIALOGUE_DATA data;					   // 30
		std::uint32_t priorityAndJournalIndex; // 34
		BGSDialogueBranch* ownerBranch;		   // 38
		TESQuest* ownerQuest;				   // 40
		BGSKeyword* subtypeKeyword;			   // 48
		TESTopicInfo** topicInfos;			   // 50
		InfoTree* infoTree;					   // 58
		std::uint32_t numTopicInfos;		   // 60
		std::uint32_t topicInfoAllocSize;	   // 64
		std::uint32_t firstFileOffset;		   // 68
		BSFixedString formEditorID;			   // 70
	};
	static_assert(sizeof(TESTopic) == 0x78);

	struct TOPIC_INFO_DATA
	{
	public:
		enum class TOPIC_INFO_FLAGS : std::uint32_t
		{
			kNone = 0,
			kStartSceneOnEnd = 0x1,
			kRandom = 0x2,
			kSayOnce = 0x4,
			kRequirePlayerActivation = 0x8,
			kInfoRefusal = 0x10,
			kRandomEnd = 0x20,
			kEndRunningScene = 0x40,
			kIsForceGreet = 0x80,
			kPlaredAddress = 0x100,
			kGroupTracksData = 0x100,
			kForceSubtitle = 0x200,
			kGroupForceRandom = 0x200,
			kCanMoveWhileGreeitng = 0x400,
			kNoLIPFile = 0x800,
			kGroupDontDoAll = 0x800,
			kPostProcess = 0x1000,
			kCustomSoundOutpt = 0x2000,
			kDialogueInfoSaid = 0x4000,
			kHasCapsData = 0x4000,
			kAlreadySaidDoAllBeforeRepeating = 0x8000,
			kEditorOnly = 0x4000,
		};

		// members
		REX::EnumSet<TOPIC_INFO_FLAGS, std::uint16_t> flags; // 00
		std::uint16_t timeUntilReset;						 // 02
	};
	static_assert(sizeof(TOPIC_INFO_DATA) == 0x4);

	struct TESResponse
	{
	public:
		struct RespData
		{
			std::uint16_t percent;
			std::uint8_t responseID;
			bool useEmotion;
		};
		static_assert(sizeof(RespData) == 0x4);

		const char* GetResponseText()
		{
			using func_t = decltype(&TESResponse::GetResponseText);
			static REL::Relocation<func_t> func{ REL::RelocationID(0, 2208288) };
			return func(this);
		}

		// Members
		BGSLocalizedString responseText;
		TESResponse* pNext;
		TESResponse::RespData data;
		BGSTypedKeywordValue<KeywordType::kAnimFaceArchetype> faceArcheType;
	};
	static_assert(sizeof(TESResponse) == 0x18);

	class ResponseListWrapper
	{
	public:
		// members
		TESResponse* head; // 00
	};
	static_assert(sizeof(ResponseListWrapper) == 0x8);

	class __declspec(novtable) TESTopicInfo
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESTopicInfo };
		inline static constexpr auto VTABLE{ VTABLE::TESTopicInfo };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kINFO };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kInfoGroup = 1 << 6,
				kExcludeFromExpert = 1 << 7,
				kIgnored = 1 << 12,
				kActorChanged = 1 << 13
			};
		};

		enum CHARISMA_CHALLENGE_DIFFICULTY : std::uint32_t
		{
			CC_CHALLENGE_NONE = 0x0,
			CC_CHALLENGE_EASY = 0x1,
			CC_CHALLENGE_MEDIUM = 0x2,
			CC_CHALLENGE_HARD = 0x3,
			CC_CHALLENGE_ALWAYS_SUCCEEDS = 0x4,
			CC_CHALLENGE_EASY_REPEATABLE = 0x5,
			CC_CHALLENGE_MEDIUM_REPEATABLE = 0x6,
			CC_CHALLENGE_HARD_REPEATABLE = 0x7,
			CC_CHALLENGE_COUNT = 0x8,
		};

		enum CHARISMA_CHALLENGE_SUCCESS : std::uint32_t
		{
			CC_SUCCESS_NONE = 0xFFFFFFFF,
			CC_SUCCESS_FAIL = 0x0,
			CC_SUCCESS_SUCCEED = 0x1,
			CC_SUCCESS_COUNT = 0x2,
		};

		// Returns nullptr if no parent.
		TESTopicInfo* GetParentInfoGroup()
		{
			using func_t = decltype(&TESTopicInfo::GetParentInfoGroup);
			static REL::Relocation<func_t> func{ REL::RelocationID(163538, 2208435) };
			return func(this);
		}

		CHARISMA_CHALLENGE_DIFFICULTY GetSpeechChallengeLevel()
		{
			using func_t = decltype(&TESTopicInfo::GetSpeechChallengeLevel);
			static REL::Relocation<func_t> func{ REL::RelocationID(0, 2208441) };
			return func(this);
		}

		CHARISMA_CHALLENGE_SUCCESS GetSuccessLevel()
		{
			using func_t = decltype(&TESTopicInfo::GetSuccessLevel);
			static REL::Relocation<func_t> func{ REL::RelocationID(1023955, 2208444) };
			return func(this);
		}

		// members
		TESTopic* parentTopic;		   // 20
		TESGlobal* resetGlobal;		   // 28
		TESTopicInfo* dataInfo;		   // 30
		TESCondition objConditions;	   // 38
		std::uint16_t infoIndex;	   // 40
		std::int8_t subtitlePriority;  // 42
		bool saidOnce;				   // 43
		TOPIC_INFO_DATA data;		   // 44
		ResponseListWrapper responses; // 48
	};
	static_assert(sizeof(TESTopicInfo) == 0x50);

	struct TOPIC_INFO_SCENEDATA
	{
		BGSScene* scene;	 // 00
		std::uint32_t phase; // 08
	};
	static_assert(sizeof(TOPIC_INFO_SCENEDATA) == 0x10);

	struct IDLE_DATA
	{
	public:
		// members
		std::int8_t loopMin;	   // 00
		std::int8_t loopMax;	   // 01
		std::int8_t flags;		   // 02
		std::uint16_t replayDelay; // 04
	};
	static_assert(sizeof(IDLE_DATA) == 0x6);

	class __declspec(novtable) TESIdleForm
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESIdleForm };
		inline static constexpr auto VTABLE{ VTABLE::TESIdleForm };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kIDLE };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		[[nodiscard]] bool CheckConditions(TESObjectREFR* a_actionRef, TESObjectREFR* a_targetRef, bool a_recurseUp) const;

		// members
		TESCondition conditions;		 // 20
		IDLE_DATA data;					 // 28
		NiFormArray* childIdles;		 // 30
		TESIdleForm* parentIdle;		 // 38
		TESIdleForm* prevIdle;			 // 40
		BSFixedString behaviorGraphName; // 48
		BSFixedString animEventName;	 // 50
		BSFixedString animFileName;		 // 58
		BSString formEditorID;			 // 60
	};
	static_assert(sizeof(TESIdleForm) == 0x70);

	class __declspec(novtable) TESLoadScreen
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESLoadScreen };
		inline static constexpr auto VTABLE{ VTABLE::TESLoadScreen };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kLSCR };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct LoadNIFData;

		// members
		TESCondition conditions;		// 20
		LoadNIFData* loadNIFData;		// 28
		BGSLocalizedString loadingText; // 30
	};
	static_assert(sizeof(TESLoadScreen) == 0x38);

	class __declspec(novtable) TESObjectANIO
		: public TESForm,			  // 00
		  public BGSModelMaterialSwap // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectANIO };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectANIO };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kANIO };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BSFixedString formEditorID;	   // 60
		BSFixedString unloadEventName; // 68
	};
	static_assert(sizeof(TESObjectANIO) == 0x70);

	struct EffectShaderData
	{
	public:
		// members
		REX::Enum<_D3DBLEND, std::int32_t> textureBlendModeSource;	// 00
		REX::Enum<_D3DBLENDOP, std::int32_t> textureBlendOperation; // 04
		REX::Enum<_D3DCMPFUNC, std::int32_t> textureZTestFunction;	// 08
		std::uint32_t fillColor1;									// 0C
		float fillAlphaFadeInTime;									// 10
		float fillAlphaFullTime;									// 14
		float fillAlphaFadeOutTime;									// 18
		float fillAlphaPersistentPercent;							// 1C
		float fillAlphaPulseAmplitude;								// 20
		float fillAlphaPulseFrequency;								// 24
		float fillTextureUAnimSpeed;								// 28
		float fillTextureVAnimSpeed;								// 2C
		float edgeExponentValue;									// 30
		std::uint32_t edgeColor;									// 34
		float edgeAlphaFadeInTime;									// 38
		float edgeAlphaFullTime;									// 3C
		float edgeAlphaFadeOutTime;									// 40
		float edgeAlphaPersistentPercent;							// 44
		float edgeAlphaPulseAmplitude;								// 48
		float edgeAlphaPulseFrequency;								// 4C
		float fillAlphaFullPercent;									// 50
		float edgeAlphaFullPercent;									// 54
		REX::Enum<_D3DBLEND, std::int32_t> textureBlendModeDest;	// 58
		float alphaTestStartTime;									// 5C
		float alphaTestEndTime;										// 60
		float alphaTestStartValue;									// 64
		float alphaTestEndValue;									// 68
		BGSSoundDescriptorForm* ambientSound;						// 70
		std::uint32_t fillColor2;									// 78
		std::uint32_t fillColor3;									// 7C
		float fillColorScaleA[3];									// 80
		float fillColorTimeA[3];									// 8C
		std::uint32_t flags;										// 98
		float fillTextureUScale;									// 9C
		float fillTextureVScale;									// A0
		std::int8_t boneDepth;										// A4
	};
	static_assert(sizeof(EffectShaderData) == 0xA8);

	class __declspec(novtable) TESEffectShader
		: public TESForm, // 000
		  public TESModel // 020
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESEffectShader };
		inline static constexpr auto VTABLE{ VTABLE::TESEffectShader };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kEFSH };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		EffectShaderData data;					 // 050
		TESTexture textureShaderTexture;		 // 0F8
		TESTexture blockOutTexture;				 // 108
		TESTexture paletteTexture;				 // 118
		NiPointer<BSGeometry> shareableGeometry; // 128
	};
	static_assert(sizeof(TESEffectShader) == 0x130);

	class __declspec(novtable) BGSDebris
		: public TESForm,		// 00
		  public BGSPreloadable // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSDebris };
		inline static constexpr auto VTABLE{ VTABLE::BGSDebris };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kDEBR };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BSSimpleList<BGSDebrisData*> dataList; // 28
	};
	static_assert(sizeof(BGSDebris) == 0x38);

	class __declspec(novtable) TESImageSpace
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESImageSpace };
		inline static constexpr auto VTABLE{ VTABLE::TESImageSpace };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kIMGS };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		ImageSpaceBaseData data;		   // 20
		TESTexture lutTexture;			   // 78
		NiPointer<NiTexture> niLutTexture; // 88
	};
	static_assert(sizeof(TESImageSpace) == 0x90);

	class __declspec(novtable) TESImageSpaceModifier
		: public TESForm // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESImageSpaceModifier };
		inline static constexpr auto VTABLE{ VTABLE::TESImageSpaceModifier };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kIMAD };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct ImageSpaceModifierData
		{
		public:
			// members
			bool animatable;								   // 00
			float duration;									   // 04
			std::uint32_t keySize[21][2];					   // 08
			std::uint32_t tintColorKeySize;					   // B0
			std::uint32_t blurKeySize;						   // B4
			std::uint32_t doubleKeySize;					   // B8
			std::uint32_t radialBlurStrengthKeySize;		   // BC
			std::uint32_t radialBlurRampupKeySize;			   // C0
			std::uint32_t radialBlurStartKeySize;			   // C4
			bool useTargetForRadialBlur;					   // C8
			NiPoint2 radialBlurCenter;						   // CC
			std::uint32_t depthOfFieldStrengthKeySize;		   // D4
			std::uint32_t depthOfFieldDistanceKeySize;		   // D8
			std::uint32_t depthOfFieldRangeKeySize;			   // DC
			bool useTargetForDepthOfField;					   // E0
			std::int8_t depthOfFieldMode;					   // E1
			std::uint32_t radialBlurRampDownKeySize;		   // E4
			std::uint32_t radialBlurDownStartKeySize;		   // E8
			std::uint32_t fadeColorKeySize;					   // EC
			std::uint32_t motionBlurStrengthKeySize;		   // F0
			std::uint32_t depthOfFieldVignetteRadiusKeySize;   // F4
			std::uint32_t depthOfFieldVignetteStrengthKeySize; // F8
		};
		static_assert(sizeof(ImageSpaceModifierData) == 0xFC);

		// members
		ImageSpaceModifierData data;											 // 020
		NiPointer<NiFloatInterpolator> interpolator[21][2];						 // 120
		NiPointer<NiFloatInterpolator> blurInterpolator;						 // 270
		NiPointer<NiFloatInterpolator> doubleInterpolator;						 // 278
		NiPointer<NiColorInterpolator> tintColorInterpolator;					 // 280
		NiPointer<NiColorInterpolator> fadeColorInterpolator;					 // 288
		NiPointer<NiFloatInterpolator> radialBlurStrengthInterpolator;			 // 290
		NiPointer<NiFloatInterpolator> radialBlurRampupInterpolator;			 // 298
		NiPointer<NiFloatInterpolator> radialBlurStartInterpolator;				 // 2A0
		NiPointer<NiFloatInterpolator> radialBlurRampDownInterpolator;			 // 2A8
		NiPointer<NiFloatInterpolator> radialBlurDownStartInterpolator;			 // 2B0
		NiPointer<NiFloatInterpolator> depthOfFieldStrengthInterpolator;		 // 2B8
		NiPointer<NiFloatInterpolator> depthOfFieldDistanceInterpolator;		 // 2C0
		NiPointer<NiFloatInterpolator> depthOfFieldRangeInterpolator;			 // 2C8
		NiPointer<NiFloatInterpolator> depthOfFieldVignetteRadiusInterpolator;	 // 2D0
		NiPointer<NiFloatInterpolator> depthOfFieldVignetteStrengthInterpolator; // 2D8
		NiPointer<NiFloatInterpolator> motionBlurStrengthInterpolator;			 // 2E0
		BSString formEditorID;													 // 2E8
	};
	static_assert(sizeof(TESImageSpaceModifier) == 0x2F8);

	class __declspec(novtable) BGSListForm
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSListForm };
		inline static constexpr auto VTABLE{ VTABLE::BGSListForm };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kFLST };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		BSContainer::ForEachResult ForEachForm(std::function<BSContainer::ForEachResult(TESForm*)> a_callback) const;

		[[nodiscard]] bool Contains(const TESForm* a_item) const;

		void AddScriptForm(const TESForm* a_form);
		bool RemoveScriptForm(const TESForm* a_form);

		// members
		BSTArray<TESForm*> arrayOfForms;		   // 20
		BSTArray<TESFormID>* scriptAddedTempForms; // 38
		std::uint32_t scriptAddedFormCount;		   // 40
	};
	static_assert(sizeof(BGSListForm) == 0x48);

	struct PerkData
	{
	public:
		// members
		bool trait;			  // 00
		std::int8_t level;	  // 01
		std::int8_t numRanks; // 02
		bool playable;		  // 03
		bool hidden;		  // 04
	};
	static_assert(sizeof(PerkData) == 0x5);

	class __declspec(novtable) BGSPerk
		: public TESForm,		 // 00
		  public TESFullName,	 // 20
		  public TESDescription, // 30
		  public TESIcon		 // 48
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSPerk };
		inline static constexpr auto VTABLE{ VTABLE::BGSPerk };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPERK };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kNonPlayable = 1 << 2,
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		PerkData data;						 // 58
		TESCondition perkConditions;		 // 60
		BSTArray<BGSPerkEntry*> perkEntries; // 68
		BGSPerk* nextPerk;					 // 80
		BGSSoundDescriptorForm* sound;		 // 88
		BSFixedStringCS swfFile;			 // 90
	};
	static_assert(sizeof(BGSPerk) == 0x98);

	struct PART_DATA
	{
	public:
		// members
		float damageMult;						   // 00
		BGSDebris* explosionGenericDebris;		   // 08
		BGSExplosion* explosion;				   // 10
		float explosionGenericDebrisScale;		   // 18
		BGSDebris* dismemberGenericDebris;		   // 20
		BGSExplosion* dismemberExplosion;		   // 28
		float dismemberGenericDebrisScale;		   // 30
		BGSDebris* onCrippleGenericDebris;		   // 38
		BGSExplosion* onCrippleExplosion;		   // 40
		float onCrippleGenericDebrisScale;		   // 48
		NiPoint3 goreTranslate;					   // 4C
		NiPoint3 goreRotate;					   // 58
		BGSImpactDataSet* dismemberImpactDataSet;  // 68
		BGSImpactDataSet* explosionImpactDataSet;  // 70
		BGSImpactDataSet* onCrippleImpactDataSet;  // 78
		ActorValueInfo* actorValue;				   // 80
		BGSArtObject* artObject;				   // 88
		float explosionSpecialDebrisScale;		   // 90
		std::uint8_t flags;						   // 94
		std::uint8_t type;						   // 95
		std::uint8_t healthPercent;				   // 96
		std::uint8_t toHitChance;				   // 97
		std::uint8_t explosionChance;			   // 98
		std::uint8_t nonLethalDismembermentChance; // 99
		std::uint8_t dismemberGenericDebrisCount;  // 9A
		std::uint8_t onCrippleGenericDebrisCount;  // 9B
		std::uint8_t explosionGenericDebrisCount;  // 9C
		std::uint8_t dismemberDecalCount;		   // 9D
		std::uint8_t onCrippleDecalCount;		   // 9E
		std::uint8_t explosionDecalCount;		   // 9F
		std::uint8_t geometrySegmentIndex;		   // A0
	};
	static_assert(sizeof(PART_DATA) == 0xA8);

	class BGSBodyPart
	{
	public:
		// members
		BSFixedString nodeName;									 // 000
		BSFixedString targetName;								 // 008
		BSFixedString hitReactionVariablePrefix;				 // 010
		BGSBodyPartDefs::HitReactionData runtimeHitReactionData; // 018
		BGSLocalizedString partName;							 // 040
		BSFixedString goreObjectName;							 // 048
		TESModel explosionSpecialDebris;						 // 050
		PART_DATA data;											 // 080
		BGSArtObject* dismemberBlood;							 // 128
		BGSMaterialType* bloodImpactMaterial;					 // 130
		BGSMaterialType* onCrippleBloodImpactMaterial;			 // 138
		BGSTextureSet* meatCapTextureSet;						 // 140
		BGSTextureSet* meatCollarTextureSet;					 // 148
	};
	static_assert(sizeof(BGSBodyPart) == 0x150);

	class __declspec(novtable) BGSBodyPartData
		: public TESForm,		// 000
		  public TESModel,		// 020
		  public BGSPreloadable // 050
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSBodyPartData };
		inline static constexpr auto VTABLE{ VTABLE::BGSBodyPartData };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kBPTD };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		enum PartType
		{
			Torso,
			Head1,
			Eye,
			LookAt,
			FlyGrab,
			Head2,
			LeftArm1,
			LeftArm2,
			RightArm1,
			RightArm2,
			LeftLeg1,
			LeftLeg2,
			LeftLeg3,
			RightLeg1,
			RightLeg2,
			RightLeg3,
			Brain,
			Weapon,
			Root,
			COM,
			Pelvis,
			Camera,
			OffsetRoot,
			LeftFoot,
			RightFoot,
			FaceTargetSource
		};

		// members
		BGSBodyPart* partArray[26];								 // 058
		BGSBodyPartDefs::HitReactionData defaultHitReactionData; // 128
	};
	static_assert(sizeof(BGSBodyPartData) == 0x150);

	class __declspec(novtable) BGSCameraShot
		: public TESForm,					 // 00
		  public TESModel,					 // 20
		  public TESImageSpaceModifiableForm // 50
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSCameraShot };
		inline static constexpr auto VTABLE{ VTABLE::BGSCameraShot };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kCAMS };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		enum class CAM_ACTION
		{
			kShoot = 0,
			kFly = 1,
			kHit = 2,
			kZoom = 3
		};

		enum class CAM_OBJECT
		{
			kAttacker = 0,
			kProjectile = 1,
			kTarget = 2,
			kLeadActor = 3
		};

		struct CAMERA_SHOT_DATA
		{
		public:
			// members
			REX::Enum<CAM_ACTION, std::uint32_t> cameraAction; // 00
			REX::Enum<CAM_OBJECT, std::uint32_t> location;	   // 04
			REX::Enum<CAM_OBJECT, std::uint32_t> target;	   // 08
			std::uint32_t flags;							   // 0C
			float playerTimeMult;							   // 10
			float targetTimeMult;							   // 14
			float globalTimeMult;							   // 18
			float maxTime;									   // 1C
			float minTime;									   // 20
			float targetPercentBetweenActors;				   // 24
			float nearTargetDistance;						   // 28
			float locationSpring;							   // 2C
			float targetSpring;								   // 30
			float rotationOffsetX;							   // 34
			float rotationOffsetY;							   // 38
			float rotationOffsetZ;							   // 3C
		};
		static_assert(sizeof(CAMERA_SHOT_DATA) == 0x40);

		// members
		CAMERA_SHOT_DATA data;	 // 60
		TESCondition conditions; // A0
	};
	static_assert(sizeof(BGSCameraShot) == 0xA8);

	struct PATH_DATA
	{
	public:
		// members
		std::int8_t flags; // 00
	};
	static_assert(sizeof(PATH_DATA) == 0x1);

	class __declspec(novtable) BGSCameraPath
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSCameraPath };
		inline static constexpr auto VTABLE{ VTABLE::BGSCameraPath };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kCPTH };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		TESCondition conditions;			// 20
		BSSimpleList<BGSCameraShot*> shots; // 28
		PATH_DATA data;						// 38
		NiFormArray* childPaths;			// 40
		BGSCameraPath* parentPath;			// 48
		BGSCameraPath* prevPath;			// 50
	};
	static_assert(sizeof(BGSCameraPath) == 0x58);

	struct VOICE_TYPE_DATA
	{
	public:
		enum class Flags
		{
			kNone = 0,
			kAllowDefaultDialogue = 1 << 0,
			kFemale = 1 << 1
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> flags;
	};
	static_assert(sizeof(VOICE_TYPE_DATA) == 0x1);

	class __declspec(novtable) BGSVoiceType
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSVoiceType };
		inline static constexpr auto VTABLE{ VTABLE::BGSVoiceType };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kVTYP };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		VOICE_TYPE_DATA data;  // 20
		BSString formEditorID; // 28
	};
	static_assert(sizeof(BGSVoiceType) == 0x38);

	class __declspec(novtable) BGSMaterialType
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMaterialType };
		inline static constexpr auto VTABLE{ VTABLE::BGSMaterialType };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kMATT };

		enum class Flags
		{
			kNone = 0,
			kStairs = 1 << 0,
			kArrowsStick = 1 << 1,
			kCanTunnel = 1 << 2
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		TESModel breakableFXModel;				  // 20
		BGSMaterialType* parentType;			  // 50
		BGSImpactDataSet* havokImpactDataSet;	  // 58
		BSFixedString materialName;				  // 60
		std::uint32_t materialID;				  // 68
		NiColor materialColor;					  // 6C
		float buoyancy;							  // 78
		REX::EnumSet<Flags, std::uint32_t> flags; // 7C
	};
	static_assert(sizeof(BGSMaterialType) == 0x80);

	struct DECAL_DATA_DATA
	{
	public:
		enum class Flags
		{
			kNone = 0,
			kNoDecalData = 1 << 0
		};

		// members
		float decalMinWidth;					 // 00
		float decalMaxWidth;					 // 04
		float decalMinHeight;					 // 08
		float decalMaxHeight;					 // 0C
		float depth;							 // 10
		float shininess;						 // 14
		float parallaxScale;					 // 18
		std::int8_t parallaxPasses;				 // 1C
		REX::EnumSet<Flags, std::uint8_t> flags; // 1D
		std::uint32_t color;					 // 20
	};
	static_assert(sizeof(DECAL_DATA_DATA) == 0x24);

	class DecalData
	{
	public:
		// members
		DECAL_DATA_DATA data; // 00
	};
	static_assert(sizeof(DecalData) == 0x24);

	class __declspec(novtable) BGSImpactData
		: public TESForm, // 00
		  public TESModel // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSImpactData };
		inline static constexpr auto VTABLE{ VTABLE::BGSImpactData };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kIPCT };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		enum class ORIENTATION
		{
			kSurfaceNormal = 0,
			kProjVector = 1,
			kProjReflect = 2
		};

		struct IMPACT_DATA_DATA
		{
		public:
			// members
			float effectDuration;							  // 00
			REX::Enum<ORIENTATION, std::uint32_t> orient;	  // 04
			float angleThreshold;							  // 08
			float placementRadius;							  // 0C
			REX::Enum<SOUND_LEVEL, std::uint32_t> soundLevel; // 10
			std::int8_t flags;								  // 14
			std::int8_t resultOverride;						  // 15
		};
		static_assert(sizeof(IMPACT_DATA_DATA) == 0x18);

		// members
		IMPACT_DATA_DATA data;			 // 50
		BGSTextureSet* decalTextureSet;	 // 68
		BGSTextureSet* decalTextureSet2; // 70
		BGSSoundDescriptorForm* sound1;	 // 78
		BGSSoundDescriptorForm* sound2;	 // 80
		BGSExplosion* explosion;		 // 88
		BGSHazard* hazard;				 // 90
		DecalData decalData;			 // 98
		float maxFootstepParticleDist;	 // BC
	};
	static_assert(sizeof(BGSImpactData) == 0xC0);

	class __declspec(novtable) BGSImpactDataSet
		: public TESForm,		// 00
		  public BGSPreloadable // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSImpactDataSet };
		inline static constexpr auto VTABLE{ VTABLE::BGSImpactDataSet };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kIPDS };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BSTHashMap<const BGSMaterialType*, BGSImpactData*> impactMap; // 28
	};
	static_assert(sizeof(BGSImpactDataSet) == 0x58);

	struct ENCOUNTER_ZONE_GAME_DATA
	{
	public:
		// members
		std::uint32_t detachTime; // 00
		std::uint32_t attachTime; // 04
		std::uint32_t resetTime;  // 08
		std::uint16_t zoneLevel;  // 0C
	};
	static_assert(sizeof(ENCOUNTER_ZONE_GAME_DATA) == 0x10);

	struct ENCOUNTER_ZONE_DATA
	{
	public:
		enum class Flags
		{
			kNeverReset = 1 << 0,
			kMatchPCBelowMin = 1 << 1,
			kDisableCombatBoundary = 1 << 2,
			kWorkshopZone = 1 << 3
		};

		// members
		TESForm* zoneOwner;						 // 00
		BGSLocation* location;					 // 08
		std::int8_t ownerRank;					 // 10
		std::int8_t minLevel;					 // 11
		REX::EnumSet<Flags, std::uint8_t> flags; // 12
		std::int8_t maxLevel;					 // 13
	};
	static_assert(sizeof(ENCOUNTER_ZONE_DATA) == 0x18);

	class __declspec(novtable) BGSEncounterZone
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEncounterZone };
		inline static constexpr auto VTABLE{ VTABLE::BGSEncounterZone };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kECZN };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		[[nodiscard]] bool NeverResets() const noexcept { return data.flags.any(ENCOUNTER_ZONE_DATA::Flags::kNeverReset); }
		[[nodiscard]] bool MatchesPCBelowMin() const noexcept { return data.flags.any(ENCOUNTER_ZONE_DATA::Flags::kMatchPCBelowMin); }
		[[nodiscard]] bool DisablesCombatBoundary() const noexcept { return data.flags.any(ENCOUNTER_ZONE_DATA::Flags::kDisableCombatBoundary); }
		[[nodiscard]] bool IsWorkshop() const noexcept { return data.flags.any(ENCOUNTER_ZONE_DATA::Flags::kWorkshopZone); }

		// members
		ENCOUNTER_ZONE_DATA data;		   // 20
		ENCOUNTER_ZONE_GAME_DATA gameData; // 38
	};
	static_assert(sizeof(BGSEncounterZone) == 0x48);

	struct UnloadedRefData
	{
	public:
		// members
		TESFormID refID;		 // 00
		TESFormID parentSpaceID; // 04
		std::uint32_t cellKey;	 // 08
	};
	static_assert(sizeof(UnloadedRefData) == 0xC);

	struct SpecialRefData
	{
	public:
		// members
		BGSLocationRefType* type; // 00
		UnloadedRefData refData;  // 08
	};
	static_assert(sizeof(SpecialRefData) == 0x18);

	struct UniqueNPCData
	{
	public:
		// members
		TESNPC* npc;			// 00
		TESFormID refID;		// 08
		BGSLocation* editorLoc; // 10
	};
	static_assert(sizeof(UniqueNPCData) == 0x18);

	class __declspec(novtable) BGSLocation
		: public TESForm,		// 000
		  public TESFullName,	// 020
		  public BGSKeywordForm // 030
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSLocation };
		inline static constexpr auto VTABLE{ VTABLE::BGSLocation };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kLCTN };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kInteriorCellsUseRefLocationForWorldMapPlayerMarker = 1 << 6,
				kIgnored = 1 << 12
			};
		};

		struct KEYWORD_DATA
		{
		public:
			// members
			BGSKeyword* keyword; // 00
			float data;			 // 08
		};
		static_assert(sizeof(KEYWORD_DATA) == 0x10);

		bool IsChild(const BGSLocation* a_possibleChild) const;
		bool IsParent(const BGSLocation* a_possibleParent) const;

		// members
		BGSLocation* parentLoc;												   // 050
		TESFaction* unreportedCrimeFaction;									   // 058
		BGSMusicType* musicType;											   // 060
		BGSEncounterZone* zone;												   // 068
		ObjectRefHandle worldLocMarker;										   // 070
		float worldLocRadius;												   // 074
		float actorFadeMult;												   // 078
		ObjectRefHandle horseLocMarker;										   // 07C
		BSTArray<SpecialRefData> specialRefs;								   // 080
		BSTArray<UniqueNPCData> uniqueNPCs;									   // 098
		OverrideData* overrideData;											   // 0B0
		BSTArray<RE::TESFormID> newUnloadedRefs;							   // 0B8
		BSTArray<BSTTuple<BGSLocationRefType*, RE::TESFormID>> newSpecialRefs; // 0D0
		NiPointer<QueuedPromoteLocationReferencesTask> promoteRefsTask;		   // 0E8
		BSTArray<ObjectRefHandle> promotedRefsArray;						   // 0F0
		volatile std::int32_t loadedCount;									   // 108
		std::uint32_t fileOffset;											   // 10C
		BSTArray<KEYWORD_DATA> keywordData;									   // 110
		mutable BSSpinLock locLoadedLock;									   // 128
		std::uint32_t lastChecked;											   // 130
		bool cleared;														   // 134
		bool everCleared;													   // 135
		mutable BSReadWriteLock locker;										   // 138
	};
	static_assert(sizeof(BGSLocation) == 0x140);

	struct MESSAGEBOX_BUTTON
	{
	public:
		F4_HEAP_REDEFINE_NEW(MESSAGEBOX_BUTTON);

		// members
		BGSLocalizedString text; // 00
		TESCondition conditions; // 08
	};
	static_assert(sizeof(MESSAGEBOX_BUTTON) == 0x10);

	class __declspec(novtable) BGSMessage
		: public TESForm,		// 00
		  public TESFullName,	// 20
		  public TESDescription // 30
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMessage };
		inline static constexpr auto VTABLE{ VTABLE::BGSMessage };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kMESG };

		enum class Flags
		{
			kNone = 0,
			kMessageBox = 1 << 0,
			kInitialDelay = 1 << 1
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		void AddButton(MESSAGEBOX_BUTTON* btn)
		{
			using func_t = decltype(&BGSMessage::AddButton);
			static REL::Relocation<func_t> func{ REL::ID(236744) };
			return func(this, btn);
		}

		std::uint32_t GetConvertedDescription(BSFixedString& a_result)
		{
			using func_t = decltype(&BGSMessage::GetConvertedDescription);
			static REL::Relocation<func_t> func{ REL::ID(8331) };
			return func(this, a_result);
		}

		// members
		BGSMenuIcon* icon;							 // 48
		TESQuest* ownerQuest;						 // 50
		BSSimpleList<MESSAGEBOX_BUTTON*> buttonList; // 58
		BSFixedStringCS swfFile;					 // 68
		BGSLocalizedString shortName;				 // 70
		REX::EnumSet<Flags, std::uint32_t> flags;	 // 78
		std::uint32_t displayTime;					 // 7C
	};
	static_assert(sizeof(BGSMessage) == 0x80);

	class __declspec(novtable) BGSLightingTemplate
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSLightingTemplate };
		inline static constexpr auto VTABLE{ VTABLE::BGSLightingTemplate };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kLGTM };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		INTERIOR_DATA data;													  // 20
		BGSGodRays* godRays;												  // B0
		BGSDirectionalAmbientLightingColors directionalAmbientLightingColors; // B8
	};
	static_assert(sizeof(BGSLightingTemplate) == 0xD8);

	class __declspec(novtable) BGSMusicType
		: public TESForm,	  // 00
		  public BSIMusicType // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMusicType };
		inline static constexpr auto VTABLE{ VTABLE::BGSMusicType };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kMUSC };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kMusicType_UsesPalette = 1 << 20
			};
		};

		// members
		BSFixedString formEditorID; // 70
	};
	static_assert(sizeof(BGSMusicType) == 0x78);

	class __declspec(novtable) BGSFootstep
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSFootstep };
		inline static constexpr auto VTABLE{ VTABLE::BGSFootstep };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kFSTP };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BSFixedString tagString;	 // 20
		BGSImpactDataSet* impactSet; // 28
	};
	static_assert(sizeof(BGSFootstep) == 0x30);

	class __declspec(novtable) BGSFootstepSet
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSFootstepSet };
		inline static constexpr auto VTABLE{ VTABLE::BGSFootstepSet };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kFSTS };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BSTArray<BGSFootstep*> entries[5]; // 20
	};
	static_assert(sizeof(BGSFootstepSet) == 0x98);

	enum class DIALOGUE_TYPE
	{
		kPlayerDialogue = 0x0,
		kCommandDialogue = 0x1,
		kSceneDialogue = 0x2,
		kCombat = 0x3,
		kFavors = 0x4,
		kDetection = 0x5,
		kService = 0x6,
		kMiscellaneous = 0x7,
	};

	enum class DIALOGUE_SUBTYPE
	{
		kPlayerDialogue_Custom = 0x0,
		kPlayerDialogue_Force_Greet = 0x1,
		kPlayerDialogue_Player_Rumor = 0x2,
		kPlayerDialogue_End = 0x3,
		kCommandDialogue_Custom = 0x3,
		kCommandDialogue_Call = 0x4,
		kCommandDialogue_Follow = 0x5,
		kCommandDialogue_Move = 0x6,
		kCommandDialogue_Attack = 0x7,
		kCommandDialogue_Inspect = 0x8,
		kCommandDialogue_Retrieve = 0x9,
		kCommandDialogue_Stay = 0xA,
		kCommandDialogue_Release = 0xB,
		kCommandDialogue_ShowRelationships = 0xC,
		kCommandDialogue_Reject = 0xD,
		kCommandDialogue_Heal = 0xE,
		kCommandDialogue_Assign = 0xF,
		kCommandDialogue_Enter = 0x10,
		kSceneDialogue_Custom = 0x11,
		kFavor_Show = 0x12,
		kFavor_Agree = 0x13,
		kFavor_Refuse = 0x14,
		kFavor_Exit_State = 0x15,
		kFavor_Morality_Refuse = 0x16,
		kFavor_Trade = 0x17,
		kFavor_Pathing_Reject = 0x18,
		kCombat_Attack = 0x19,
		kCombat_Power_Attack = 0x1A,
		kCombat_Bash = 0x1B,
		kCombat_Hit = 0x1C,
		kCombat_Flee = 0x1D,
		kCombat_Bleed_Out = 0x1E,
		kCombat_Avoid_Threat = 0x1F,
		kCombat_Death = 0x20,
		kCombat_Block = 0x21,
		kCombat_Taunt = 0x22,
		kCombat_Throw_Grenade = 0x23,
		kCombat_Ally_Killed = 0x24,
		kCombat_Order_Fallback = 0x25,
		kCombat_Order_Advance = 0x26,
		kCombat_Order_Flank = 0x27,
		kCombat_Order_Take_Cover = 0x28,
		kCombat_Fallback = 0x29,
		kCombat_Request_Support = 0x2A,
		kCombat_Provide_Support = 0x2B,
		kCombat_Crippled_Limb = 0x2C,
		kCombat_Paired_Attack = 0x2D,
		kCombat_Steal = 0x2E,
		kCombat_Yield = 0x2F,
		kCombat_Accept_Yield = 0x30,
		kCombat_Pickpocket = 0x31,
		kCombat_Assault = 0x32,
		kCombat_Murder = 0x33,
		kCombat_Assault_NC = 0x34,
		kCombat_Murder_NC = 0x35,
		kCombat_Pickpocket_NC = 0x36,
		kCombat_Steal_NC = 0x37,
		kCombat_Trespass_NC = 0x38,
		kCombat_Guard_Trespass = 0x39,
		kCombat_Unused = 0x3A,
		kCombat_Voice_Power_Start = 0x3B,
		kCombat_Voice_Power_Start_Short = 0x3B,
		kCombat_Voice_Power_Start_Long = 0x3C,
		kCombat_Voice_Power_End_Short = 0x3D,
		kCombat_Voice_Power_End_Long = 0x3E,
		kCombat_Voice_Power_End = 0x3E,
		kDetection_Alert_Idle = 0x3F,
		kDetection_Lost_Idle = 0x40,
		kDetection_Normal_To_Alert = 0x41,
		kDetection_Normal_To_Combat = 0x42,
		kDetection_Normal_To_Lost = 0x43,
		kDetection_Alert_To_Normal = 0x44,
		kDetection_Alert_To_Combat = 0x45,
		kDetection_Combat_To_Normal = 0x46,
		kDetection_Combat_To_Lost = 0x47,
		kDetection_Lost_To_Normal = 0x48,
		kDetection_Lost_To_Combat = 0x49,
		kDetection_Detect_Friend_Die = 0x4A,
		kService_Refusal = 0x4B,
		kService_Repair = 0x4C,
		kService_Travel = 0x4D,
		kService_Training = 0x4E,
		kService_Barter_Exit = 0x4F,
		kService_Repair_Exit = 0x50,
		kService_Recharge = 0x51,
		kService_Recharge_Exit = 0x52,
		kService_Training_Exit = 0x53,
		kMisc_Observe_Combat = 0x54,
		kMisc_Corpse = 0x55,
		kMisc_Time_To_Go = 0x56,
		kMisc_Goodbye = 0x57,
		kMisc_Hello = 0x58,
		kMisc_Player_Action_Swing_Melee_Weapon = 0x59,
		kMisc_Player_Action_Shoot_Bow = 0x5A,
		kMisc_Player_Action_Z_Key_Object = 0x5B,
		kMisc_Player_Action_Jumping = 0x5C,
		kMisc_Player_Action_Knocking_Over_Objects = 0x5D,
		kMisc_Player_Action_Destroy_Object = 0x5E,
		kMisc_Player_Action_Stand_On_Furniture = 0x5F,
		kMisc_Player_Action_Locked_Object = 0x60,
		kMisc_Player_Action_Pickpocket = 0x61,
		kMisc_Pursue_Idle = 0x62,
		kMisc_InfoData = 0x63,
		kMisc_SceneChoice = 0x64,
		kMisc_Player_Action_Cast_Projectile_Spell = 0x65,
		kMisc_Player_Action_Cast_Self_Spell = 0x66,
		kMisc_Player_Action_Shout = 0x67,
		kMisc_Idle = 0x68,
		kMisc_Breath_Sprint_Sound = 0x69,
		kMisc_Breath_Enter_Bow_Zoom_Sound = 0x6A,
		kMisc_Breath_Exit_Bow_Zoom_Sound = 0x6B,
		kMisc_Actor_Collide_With_Actor = 0x6C,
		kMisc_Player_Iron_Sights = 0x6D,
		kMisc_Out_Off_Breath_Sound = 0x6E,
		kMisc_Combat_Grunt = 0x6F,
		kMisc_Breath_Leave_Water = 0x70,
		kMisc_Impatient_Positive = 0x71,
		kMisc_Impatient_Negative = 0x72,
		kMisc_Impatient_Neutral = 0x73,
		kMisc_Impatient_Question = 0x74,
		kMisc_Waiting_Player_Input = 0x75,
		kMisc_Greeting = 0x76,
		kMisc_Player_Activate_Door = 0x77,
		kMisc_Player_Activate_Terminals = 0x78,
		kMisc_Player_Activate_Furniture = 0x79,
		kMisc_Player_Activate_Activators = 0x7A,
		kMisc_Player_Activate_Container = 0x7B,
		kMisc_Player_Aquire_Featured_Item = 0x7C,
	};

	class __declspec(novtable) BGSDialogueBranch
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSDialogueBranch };
		inline static constexpr auto VTABLE{ VTABLE::BGSDialogueBranch };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kDLBR };

		enum class Flags
		{
			kNone = 0,
			kTopLevel = 1 << 0,
			kBlocking = 1 << 1,
			kExclusive = 1 << 2
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		REX::EnumSet<Flags, std::uint32_t> flags;	  // 20
		TESQuest* quest;							  // 28
		TESTopic* startingTopic;					  // 30
		REX::Enum<DIALOGUE_TYPE, std::uint32_t> type; // 38
	};
	static_assert(sizeof(BGSDialogueBranch) == 0x40);

	class __declspec(novtable) BGSMusicTrackFormWrapper
		: public TESForm,	   // 00
		  public BSIMusicTrack // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMusicTrackFormWrapper };
		inline static constexpr auto VTABLE{ VTABLE::BGSMusicTrackFormWrapper };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kMUST };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BGSMusicTrack* trackImpl; // 30
	};
	static_assert(sizeof(BGSMusicTrackFormWrapper) == 0x38);

	class __declspec(novtable) TESWordOfPower
		: public TESForm,	 // 00
		  public TESFullName // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESWordOfPower };
		inline static constexpr auto VTABLE{ VTABLE::TESWordOfPower };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kWOOP };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BGSLocalizedString translation; // 30
	};
	static_assert(sizeof(TESWordOfPower) == 0x38);

	class __declspec(novtable) TESShout
		: public TESForm,			   // 00
		  public TESFullName,		   // 20
		  public BGSMenuDisplayObject, // 30
		  public BGSEquipType,		   // 40
		  public TESDescription		   // 50
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESShout };
		inline static constexpr auto VTABLE{ VTABLE::TESShout };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kSHOU };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct Variation
		{
		public:
			// members
			TESWordOfPower* word; // 00
			SpellItem* spell;	  // 08
			float recoveryTime;	  // 10
		};
		static_assert(sizeof(Variation) == 0x18);

		// members
		Variation variations[3]; // 68
	};
	static_assert(sizeof(TESShout) == 0xB0);

	class __declspec(novtable) BGSEquipSlot
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEquipSlot };
		inline static constexpr auto VTABLE{ VTABLE::BGSEquipSlot };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kEQUP };

		enum class Flags
		{
			kNone = 0,
			kUseAllParents = 1 << 0,
			kParentsOptional = 1 << 1,
			kItemSlot = 1 << 2
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BSTArray<BGSEquipSlot*> parentSlots;	  // 20
		REX::EnumSet<Flags, std::uint32_t> flags; // 38
		ActorValueInfo* conditionActorValue;	  // 40
	};
	static_assert(sizeof(BGSEquipSlot) == 0x48);

	class __declspec(novtable) BGSRelationship
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSRelationship };
		inline static constexpr auto VTABLE{ VTABLE::BGSRelationship };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kRELA };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		TESNPC* npc1;				   // 20
		TESNPC* npc2;				   // 28
		BGSAssociationType* assocType; // 30
		std::uint32_t packedData;	   // 38
	};
	static_assert(sizeof(BGSRelationship) == 0x40);

	struct BGSScenePhase
	{
	public:
		// members
		TESCondition startConditions;	   // 00
		TESCondition completionConditions; // 08
		std::uint16_t phaseFlags;		   // 10
		bool active;					   // 12
		bool scriptEndRun;				   // 13
		bool runEnd;					   // 14
	};
	static_assert(sizeof(BGSScenePhase) == 0x18);

	class __declspec(novtable) BGSScene
		: public TESForm,		  // 00
		  public IKeywordFormBase // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSScene };
		inline static constexpr auto VTABLE{ VTABLE::BGSScene };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kSCEN };

		enum class Flags
		{
			kNone = 0,
			kBeginOnQuestStart = 1 << 0,
			kStopOnQuestEnd = 1 << 1,
			kRepeatConditionsWhileTrue = 1 << 3,
			kInterruptible = 1 << 4
		};

		enum class SCENE_ACTOR_FLAGS // LNAM
		{
			kNone = 0,
			kNoPlayerActivation = 1 << 0,
			kOptional = 1 << 1,
			kRunOnlyScenePackages = 1 << 2,
			kNoCommandState = 1 << 3
		};

		enum class BehaviourFlags // DNAM
		{
			kNone = 0,
			kDeathPause = 1 << 0, // unused
			kDeathEnd = 1 << 1,
			kCombatPause = 1 << 2,
			kCombatEnd = 1 << 3,
			kDialoguePause = 1 << 4,
			kDialogueEnd = 1 << 5,
			kOBS_COMPause = 1 << 6,
			kOBS_COMEnd = 1 << 7
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		NiTFlags<std::uint32_t, BGSScene> niFlags;									 // 28
		BSTArray<BGSScenePhase*> phases;											 // 30
		BSTArray<TESFormID> actors;													 // 48
		BSTArray<REX::EnumSet<SCENE_ACTOR_FLAGS, std::uint32_t>> actorFlags;		 // 60
		BSTArray<REX::EnumSet<BehaviourFlags, std::uint32_t>> actorProgressionFlags; // 78
		BSTArray<BGSSceneAction*> actions;											 // 90
		TESQuest* parentQuest;														 // A8
		BGSScene* templateScene;													 // B0
		REX::EnumSet<Flags, std::uint32_t> flags;									 // B8
		TESCondition repeatConditions;												 // C0
		std::uint32_t speakerID;													 // C8
		std::uint32_t currentActivePhase;											 // CC
		std::uint32_t startPhase;													 // D0
		float randomSceneTimer;														 // D4
		float maxREFDistanceCenter;													 // D8
		ObjectRefHandle targetRef;													 // DC
		bool shouldNotRotateToTrack;												 // E0
	};
	static_assert(sizeof(BGSScene) == 0xE8);

	class __declspec(novtable) BGSAssociationType
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAssociationType };
		inline static constexpr auto VTABLE{ VTABLE::BGSAssociationType };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kASTP };

		enum class Flags
		{
			kNone = 0,
			kFamily = 1 << 0,
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BSFixedStringCS associationLabel[2][2];	  // 20
		REX::EnumSet<Flags, std::uint32_t> flags; // 40
	};
	static_assert(sizeof(BGSAssociationType) == 0x48);

	class __declspec(novtable) BGSOutfit
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSOutfit };
		inline static constexpr auto VTABLE{ VTABLE::BGSOutfit };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kOTFT };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BSTArray<TESForm*> outfitItems; // 20
	};
	static_assert(sizeof(BGSOutfit) == 0x38);

	class __declspec(novtable) BGSMaterialObject
		: public TESForm,		  // 00
		  public TESModel,		  // 20
		  public BSMaterialObject // 50
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMaterialObject };
		inline static constexpr auto VTABLE{ VTABLE::BGSMaterialObject };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kMATO };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct FILE_DATA
		{
		public:
			// members
			std::int8_t* nuffer;	  // 00
			std::uint32_t bufferSize; // 08
		};
		static_assert(sizeof(FILE_DATA) == 0x10);

		// members
		BSTArray<FILE_DATA> fileData; // A0
	};
	static_assert(sizeof(BGSMaterialObject) == 0xB8);

	class __declspec(novtable) BGSMovementType
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMovementType };
		inline static constexpr auto VTABLE{ VTABLE::BGSMovementType };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kMOVT };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		Movement::TypeData movementTypeData; // 20
	};
	static_assert(sizeof(BGSMovementType) == 0xA0);

	class __declspec(novtable) BGSSoundDescriptorForm
		: public TESForm,			// 00
		  public BSISoundDescriptor // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSoundDescriptorForm };
		inline static constexpr auto VTABLE{ VTABLE::BGSSoundDescriptorForm };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kSNDR };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BGSSoundDescriptor* impl; // 28
	};
	static_assert(sizeof(BGSSoundDescriptorForm) == 0x30);

	class __declspec(novtable) BGSSoundCategory
		: public TESForm,		  // 00
		  public TESFullName,	  // 20
		  public BSISoundCategory // 30
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSoundCategory };
		inline static constexpr auto VTABLE{ VTABLE::BGSSoundCategory };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kSNCT };

		enum class Flags // FNAM
		{
			kNone = 0,
			kMuteWhenSubmerged = 1 << 0,
			kShouldAppearOnMenu = 1 << 1,
			kImmuneToTimeSpeedup = 1 << 2,
			kPauseDuringMenus_Immed = 1 << 3,
			kPauseDuringMenus_Faded = 1 << 4,
			kExcludeFromPlayerOPMOverride = 1 << 5,
			kPauseDuringStartMenu = 1 << 6
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BGSSoundCategory* parentCategory;			 // 38
		BGSSoundCategory* sliderCategory;			 // 40
		float volumeMult;							 // 48
		float snapshotMult;							 // 4C
		float currCompressionMult;					 // 50
		float fullyCompressedMult;					 // 54
		float frequencyMult;						 // 58
		float minFrequencyMult;						 // 5C
		REX::EnumSet<Flags, std::uint32_t> appFlags; // 60
		std::uint16_t attenuation[6];				 // 64
		std::uint16_t stateFlags;					 // 70
		std::uint16_t staticMult;					 // 72
		std::uint16_t defaultMenuValue;				 // 74
	};
	static_assert(sizeof(BGSSoundCategory) == 0x78);

	class __declspec(novtable) BGSSoundOutput
		: public TESForm,			 // 00
		  public BSISoundOutputModel // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSoundOutput };
		inline static constexpr auto VTABLE{ VTABLE::BGSSoundOutput };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kSOPM };

		enum class Flags
		{
			kNone = 0,
			kAttenuatesWithDistance = 1 << 0,
			kAllowsRumble = 1 << 1,
			kAppliesDoppler = 1 << 2,
			kAppliesDistantDelay = 1 << 3,
			kPlayerOutputModel = 1 << 4,
			kTryPlayOnController = 1 << 5,
			kCausesDucking = 1 << 6,
			kAvoidsDucking = 1 << 7
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		enum class SPEAKER_OUTPUT_MODE // MNAM
		{
			kUsesHRTF = 0,
			kDefinedSpeakerOutput = 1
		};

		struct DynamicAttenuationCharacteristics;
		struct SpeakerArrays;

		// members
		DynamicAttenuationCharacteristics* attenuation;		// 28
		SpeakerArrays* speakerOutputArrays;					// 30
		BGSAudioEffectChain* effectChain;					// 38
		REX::EnumSet<Flags, std::uint32_t> flags;			// 40
		REX::Enum<SPEAKER_OUTPUT_MODE, std::uint32_t> mode; // 44
		std::uint16_t staticAttenuation;					// 48
	};
	static_assert(sizeof(BGSSoundOutput) == 0x50);

	class __declspec(novtable) BGSCollisionLayer
		: public TESForm,		// 00
		  public TESDescription // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSCollisionLayer };
		inline static constexpr auto VTABLE{ VTABLE::BGSCollisionLayer };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kCOLL };

		enum class Flags
		{
			kNone = 0,
			kTriggerVolume = 1 << 0,
			kSensor = 1 << 1,
			kNavMeshObstacle = 1 << 2
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		std::uint32_t collisionIdx;				   // 38
		std::uint32_t debugColor;				   // 3C
		REX::EnumSet<Flags, std::uint32_t> flags;  // 40
		BSFixedString name;						   // 48
		BSTArray<BGSCollisionLayer*> collidesWith; // 50
	};
	static_assert(sizeof(BGSCollisionLayer) == 0x68);

	class __declspec(novtable) BGSColorForm
		: public TESForm,	 // 00
		  public TESFullName // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSColorForm };
		inline static constexpr auto VTABLE{ VTABLE::BGSColorForm };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kCLFM };

		enum class Flags
		{
			kNone = 0,
			kPlayable = 1 << 0,
			kRemappingIndex = 1 << 1,
			kExtendedLUT = 1 << 2
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kNonPlayable = 1 << 2,
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		union
		{
			std::uint32_t color;
			float remappingIndex;
		}; // 30
		TESCondition conditions;				  // 38
		REX::EnumSet<Flags, std::uint32_t> flags; // 40
	};
	static_assert(sizeof(BGSColorForm) == 0x48);

	class __declspec(novtable) BGSReverbParameters
		: public TESForm,	   // 00
		  public BSIReverbType // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSReverbParameters };
		inline static constexpr auto VTABLE{ VTABLE::BGSReverbParameters };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kREVB };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		enum class ReverbClass
		{
			kDefault,
			kClassA,
			kClassB,
			kClassC,
			kClassD,
			kClassE
		};

		struct ReverbParams
		{
		public:
			// members
			std::uint16_t decayTime;	 // 00
			std::uint16_t hfReference;	 // 02
			std::int8_t roomFilter;		 // 04
			std::int8_t roomHFFilter;	 // 05
			std::int8_t reflections;	 // 06
			std::int8_t reverb;			 // 07
			std::int8_t decayHFRatio;	 // 08
			std::int8_t reflectionDelay; // 09
			std::int8_t reverbDelay;	 // 0A
			std::int8_t diffusionPct;	 // 0B
			std::int8_t densityPct;		 // 0C
		};
		static_assert(sizeof(ReverbParams) == 0xE);

		// members
		ReverbParams data;		   // 28
		std::uint32_t reverbClass; // 38
	};
	static_assert(sizeof(BGSReverbParameters) == 0x40);

	class __declspec(novtable) BGSPackIn
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSPackIn };
		inline static constexpr auto VTABLE{ VTABLE::BGSPackIn };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kPKIN };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kPrefab = 1 << 9,
				kIgnored = 1 << 12
			};
		};
	};
	static_assert(sizeof(BGSPackIn) == 0x20);

	class __declspec(novtable) BGSAimModel
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAimModel };
		inline static constexpr auto VTABLE{ VTABLE::BGSAimModel };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kAMDL };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct Data
		{
		public:
			// members
			float aimModelMinConeDegrees;				 // 00
			float aimModelMaxConeDegrees;				 // 04
			float aimModelConeIncreasePerShot;			 // 08
			float aimModelConeDecreasePerSec;			 // 0C
			std::uint32_t aimModelConeDecreaseDelayMs;	 // 10
			float aimModelConeSneakMultiplier;			 // 14
			float aimModelRecoilDiminishSpringForce;	 // 18
			float aimModelRecoilDiminishSightsMult;		 // 1C
			float aimModelRecoilMaxDegPerShot;			 // 20
			float aimModelRecoilMinDegPerShot;			 // 24
			float aimModelRecoilHipMult;				 // 28
			std::uint32_t aimModelRecoilShotsForRunaway; // 2C
			float aimModelRecoilArcDeg;					 // 30
			float aimModelRecoilArcRotateDeg;			 // 34
			float aimModelConeIronSightsMultiplier;		 // 38
			float aimModelBaseStability;				 // 3C
		};
		static_assert(sizeof(Data) == 0x40);

		// members
		Data aimModelData; // 20
	};
	static_assert(sizeof(BGSAimModel) == 0x60);

	class __declspec(novtable) BGSConstructibleObject
		: public TESForm,				 // 00
		  public BGSPickupPutdownSounds, // 20
		  public TESDescription			 // 38
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSConstructibleObject };
		inline static constexpr auto VTABLE{ VTABLE::BGSConstructibleObject };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kCOBJ };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct ConstructibleObjectData
		{
		public:
			// members
			std::uint16_t numConstructed;	// 00
			std::uint16_t workshopPriority; // 02
		};
		static_assert(sizeof(ConstructibleObjectData) == 0x4);

		[[nodiscard]] TESForm* GetCreatedItem() const noexcept { return createdItem; }
		[[nodiscard]] std::uint16_t GetWorkshopPriority() const noexcept { return data.workshopPriority; }

		// members
		BSTArray<BSTTuple<TESForm*, BGSTypedFormValuePair::SharedVal>>* requiredItems; // 50
		TESCondition conditions;													   // 58
		TESForm* createdItem;														   // 60
		BGSKeyword* benchKeyword;													   // 68
		BGSConstructibleObject::ConstructibleObjectData data;						   // 70
		BGSTypedKeywordValueArray<KeywordType::kRecipeFilter> filterKeywords;		   // 78
	};
	static_assert(sizeof(BGSConstructibleObject) == 0x88);

	class __declspec(novtable) BGSMaterialSwap
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMaterialSwap };
		inline static constexpr auto VTABLE{ VTABLE::BGSMaterialSwap };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kMSWP };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kCustomSwap = 1 << 16
			};
		};

		struct Entry
		{
		public:
			// members
			BSFixedString swapMaterial; // 00
			float colorRemappingIndex;	// 08
		};
		static_assert(sizeof(Entry) == 0x10);

		// members
		BSTHashMap<BSFixedString, Entry> swapMap; // 20
	};
	static_assert(sizeof(BGSMaterialSwap) == 0x50);

	class __declspec(novtable) BGSZoomData
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSZoomData };
		inline static constexpr auto VTABLE{ VTABLE::BGSZoomData };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kZOOM };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct Data
		{
		public:
			enum class OverlayType
			{
				kDefault,
				kFine,
				kDuplex,
				kGerman,
				kDot,
				kMilitaryDot,
				kCircle,
				kOldRangefind,
				kModernRangefind,
				kSVD,
				kHandPainted,
				kBinoculars,
				kCross,
				kDoubleZero,
				kRangefinder01,
				kRangefinder02,
				kRectangle
			};

			// members
			float fovMult;								   // 00
			REX::Enum<OverlayType, std::uint32_t> overlay; // 04
			TESFormID isModFormID;						   // 08
			NiPoint3 cameraOffset;						   // 0C
		};
		static_assert(sizeof(Data) == 0x18);

		// members
		Data zoomData;				  // 20
		TESImageSpaceModifier* isMod; // 38
	};
	static_assert(sizeof(BGSZoomData) == 0x40);

	class __declspec(novtable) BGSInstanceNamingRules
		: public TESForm // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSInstanceNamingRules };
		inline static constexpr auto VTABLE{ VTABLE::BGSInstanceNamingRules };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kINNR };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
			};
		};

		class RuleData
		{
		public:
			enum class OperatorType
			{
				kGreaterThanEqual = 0,
				kGreaterThan = 1,
				kLessThanEqual = 2,
				kLessThan = 3,
				kEqual = 4
			};

			// members
			BGSLocalizedString text;							// 00
			BGSKeywordForm keywords;							// 08
			float compareVal;									// 28
			std::int8_t propertyBridgeArrayIndex;				// 2C
			REX::Enum<OperatorType, std::uint8_t> operatorType; // 2D
			std::uint16_t index;								// 2E
			bool revert;										// 30
		};
		static_assert(sizeof(RuleData) == 0x38);

		struct RuleSet
			: public BSTArray<RuleData> // 00
		{
		public:
		};
		static_assert(sizeof(RuleSet) == 0x18);

		// members
		ENUM_FORMTYPE type;									  // 020
		RuleSet ruleSets[10];								  // 028
		BSTArray<const BGSInstanceNamingRules*> mergeSources; // 118
	};
	static_assert(sizeof(BGSInstanceNamingRules) == 0x130);

	class __declspec(novtable) BGSSoundKeywordMapping
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSoundKeywordMapping };
		inline static constexpr auto VTABLE{ VTABLE::BGSSoundKeywordMapping };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kKSSM };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BSTSet<BGSKeyword*> keywordSet;									  // 20
		BSTHashMap<std::uint32_t, BGSSoundDescriptorForm*> reverbDescMap; // 50
		BGSSoundDescriptorForm* descriptor;								  // 80
		BGSSoundDescriptorForm* exteriorTail;							  // 88
		BGSSoundDescriptorForm* vatsDescriptor;							  // 90
		float vatsDescThreshold;										  // 98
	};
	static_assert(sizeof(BGSSoundKeywordMapping) == 0xA0);

	class __declspec(novtable) BGSAudioEffectChain
		: public TESForm,			 // 00
		  public BSIAudioEffectChain // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAudioEffectChain };
		inline static constexpr auto VTABLE{ VTABLE::BGSAudioEffectChain };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kAECH };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BSTArray<BSIAudioEffectParameters*> effects; // 28
	};
	static_assert(sizeof(BGSAudioEffectChain) == 0x40);

	class __declspec(novtable) BGSAttractionRule
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAttractionRule };
		inline static constexpr auto VTABLE{ VTABLE::BGSAttractionRule };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kAORU };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct ATTRACTION_RULE_DATA
		{
		public:
			// members
			float radius;	   // 00
			float minDelay;	   // 04
			float maxDelay;	   // 08
			bool requiresLOS;  // 0C
			bool combatTarget; // 0D
		};
		static_assert(sizeof(ATTRACTION_RULE_DATA) == 0x10);

		// members
		ATTRACTION_RULE_DATA data;	// 20
		BSFixedString formEditorID; // 30
	};
	static_assert(sizeof(BGSAttractionRule) == 0x38);

	class __declspec(novtable) BGSSoundCategorySnapshot
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSoundCategorySnapshot };
		inline static constexpr auto VTABLE{ VTABLE::BGSSoundCategorySnapshot };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kSCSN };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BSTHashMap<BGSSoundCategory*, float> categoryMult; // 20
		std::int8_t priority;							   // 50
	};
	static_assert(sizeof(BGSSoundCategorySnapshot) == 0x58);

	class __declspec(novtable) BGSSoundTagSet
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSoundTagSet };
		inline static constexpr auto VTABLE{ VTABLE::BGSSoundTagSet };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kSTAG };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		// members
		BSTHashMap<BSFixedString, BGSSoundDescriptorForm*> soundTags; // 20
	};
	static_assert(sizeof(BGSSoundTagSet) == 0x50);

	class BSLensFlareRenderData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSLensFlareRenderData };

		// members
		float fadeDistRadiusScale;								  // 00
		float colorInfluence;									  // 04
		BSTArray<NiPointer<BSLensFlareSpriteRenderData>> sprites; // 08
		mutable BSSpinLock lock;								  // 20
		std::uint32_t refCount;									  // 28
	};
	static_assert(sizeof(BSLensFlareRenderData) == 0x30);

	class __declspec(novtable) BGSLensFlare
		: public TESForm,			   // 00
		  public BSLensFlareRenderData // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSLensFlare };
		inline static constexpr auto VTABLE{ VTABLE::BGSLensFlare };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kLENS };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
	};
	static_assert(sizeof(BGSLensFlare) == 0x50);

	class __declspec(novtable) BGSGodRays
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSGodRays };
		inline static constexpr auto VTABLE{ VTABLE::BGSGodRays };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kGDRY };

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		struct GodRaysData
		{
		public:
			// members
			NiColor colorAir;  // 00
			NiColor colorBack; // 0C
			NiColor colorFwd;  // 18
			float intensity;   // 24
			float scatterAir;  // 28
			float scatterBack; // 2C
			float scatterFwd;  // 30
			float phaseBack;   // 34
			float phaseFwd;	   // 38
		};
		static_assert(sizeof(GodRaysData) == 0x3C);

		// members
		GodRaysData data; // 20
	};
	static_assert(sizeof(BGSGodRays) == 0x60);
}

namespace std
{
	[[nodiscard]] inline std::string to_string(RE::ENUM_FORMTYPE a_formType)
	{
		return RE::TESForm::GetFormTypeString(a_formType);
	}
}

namespace std
{
	template <>
	struct formatter<RE::ENUM_FORMTYPE>
		: public formatter<string_view>
	{
		constexpr auto parse(format_parse_context& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <class FormatContext>
		constexpr auto format(RE::ENUM_FORMTYPE a_formType, FormatContext& a_ctx) const
		{
			return formatter<string_view>::format(RE::TESForm::GetFormTypeString(a_formType), a_ctx);
		}
	};
}

#ifdef FMT_VERSION
namespace fmt
{
	template <>
	struct formatter<RE::ENUM_FORMTYPE>
		: public formatter<string_view>
	{
		constexpr auto parse(format_parse_context& a_ctx) const
		{
			return a_ctx.begin();
		}

		template <typename FormatContext>
		constexpr auto format(RE::ENUM_FORMTYPE a_formType, FormatContext& a_ctx) const
		{
			return formatter<string_view>::format(RE::TESForm::GetFormTypeString(a_formType), a_ctx);
		}
	};
}
#endif
