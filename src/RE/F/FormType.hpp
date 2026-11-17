#pragma once

namespace RE
{
	enum class FormType : std::int32_t
	{
		None,					 // 0x00 NONE X `TESForm`
								 //           X `BGSStoryManagerNodeBase`
								 //           X `BGSStoryManagerTreeForm`
								 //           X `MagicItem`
								 //           X `TESActorBase`
								 //           X `TESBoundAnimObject`
								 //           X `TESBoundObject`
								 //           X `TESObject`
		PluginHeader,			 // 0x01 TES4 X
		PluginGroup,			 // 0x02 GRUP X
		GameSetting,			 // 0x03 GMST X
		Keyword,				 // 0x04 KYWD X `BGSKeyword`
		LocationRefType,		 // 0x05 LCRT X `BGSLocationRefType`
		Action,					 // 0x06 AACT X `BGSAction`
		Transform,				 // 0x07 TRNS X `BGSTransform`
		Component,				 // 0x08 CMPO X `BGSComponent`
		TextureSet,				 // 0x09 TXST X `BGSTextureSet`
		MenuIcon,				 // 0x0A MICN X `BGSMenuIcon`
		GlobalVariable,			 // 0x0B GLOB X `TESGlobal`
		DamageType,				 // 0x0C DMGT X `BGSDamageType`
		Class,					 // 0x0D CLAS X `TESClass`
		Faction,				 // 0x0E FACT X `TESFaction`
		HeadPart,				 // 0x0F HDPT X `BGSHeadPart`
		Eyes,					 // 0x10 EYES X `TESEyes`
		Race,					 // 0x11 RACE X `TESRace`
		SoundMarker,			 // 0x12 SOUN X `TESSound`
		AcousticSpace,			 // 0x13 ASPC X `BGSAcousticSpace`
		Skill,					 // 0x14 SKIL X
		MagicEffect,			 // 0x15 MGEF X `EffectSetting`
		Script,					 // 0x16 SCPT X `Script`
		LandscapeTexture,		 // 0x17 LTEX X TESLandTexture
		Enchantment,			 // 0x18 ENCH X `EnchantmentItem`
		Spell,					 // 0x19 SPEL X `SpellItem`
		Scroll,					 // 0x1A SCRL X `ScrollItem`
		Activator,				 // 0x1B ACTI X `TESObjectACTI`
		TalkingActivator,		 // 0x1C TACT X `BGSTalkingActivator`
		Armor,					 // 0x1D ARMO X `TESObjectARMO`
		Book,					 // 0x1E BOOK X `TESObjectBOOK`
		Container,				 // 0x1F CONT X `TESObjectCONT`
		Door,					 // 0x20 DOOR X `TESObjectDOOR`
		Ingredient,				 // 0x21 INGR X `IngredientItem`
		Light,					 // 0x22 LIGH X `TESObjectLIGH`
		MiscObject,				 // 0x23 MISC X `TESObjectMISC`
		Static,					 // 0x24 STAT X `TESObjectSTAT`
		StaticCollection,		 // 0x25 SCOL X `BGSStaticCollection`
		MovableStatic,			 // 0x26 MSTT X `BGSMovableStatic`
		Grass,					 // 0x27 GRAS X `TESGrass`
		Tree,					 // 0x28 TREE X `TESObjectTREE`
		Flora,					 // 0x29 FLOR X `TESFlora`
		Furniture,				 // 0x2A FURN X `TESFurniture`
		Weapon,					 // 0x2B WEAP X `TESObjectWEAP`
		Ammo,					 // 0x2C AMMO X `TESAmmo`
		ActorBase,				 // 0x2D NPC_ X `TESNPC`
		LeveledActor,			 // 0x2E LVLN X `TESLevCharacter`
		Key,					 // 0x2F KEYM X `TESKey`
		Potion,					 // 0x30 ALCH X `AlchemyItem`
		IdleMarker,				 // 0x31 IDLM X `BGSIdleMarker`
		Note,					 // 0x32 NOTE X `BGSNote`
		Projectile,				 // 0x33 PROJ X `BGSProjectile`
		Hazard,					 // 0x34 HAZD X `BGSHazard`
		BendableSpline,			 // 0x35 BNDS X `BGSBendableSpline`
		SoulGem,				 // 0x36 SLGM X `TESSoulGem`
		Terminal,				 // 0x37 TERM X `BGSTerminal`
		LeveledItem,			 // 0x38 LVLI X `TESLevItem`
		Weather,				 // 0x39 WTHR X `TESWeather`
		Climate,				 // 0x3A CLMT X `TESClimate`
		ShaderParticleGeometry,	 // 0x3B SPGD X `BGSShaderParticleGeometryData`
		VisualEffect,			 // 0x3C RFCT X `BGSReferenceEffect`
		Region,					 // 0x3D REGN X `TESRegion`
		NavMeshInfoMap,			 // 0x3E NAVI X `NavMeshInfoMap`
		Cell,					 // 0x3F CELL X `TESObjectCELL`
		ObjectReference,		 // 0x40 REFR X `TESObjectREFR`
								 //           X `Explosion`
								 //           X `Projectile`
		Actor,					 // 0x41 ACHR X `Actor`
								 //           X `PlayerCharacter`
		MissileProjectile,		 // 0x42 PMIS X `MissileProjectile`
		ArrowProjectile,		 // 0x43 PARW X `ArrowProjectile`
		GrenadeProjectile,		 // 0x44 PGRE X `GrenadeProjectile`
		BeamProjectile,			 // 0x45 PBEA X `BeamProjectile`
		FlameProjectile,		 // 0x46 PFLA X `FlameProjectile`
		ConeProjectile,			 // 0x47 PCON X `ConeProjectile`
		BarrierProjectile,		 // 0x48 PBAR X `BarrierProjectile`
		PlacedHazard,			 // 0x49 PHZD X `Hazard`
		WorldSpace,				 // 0x4A WRLD X `TESWorldSpace`
		Landscape,				 // 0x4B LAND X `TESObjectLAND`
		NavMesh,				 // 0x4C NAVM X `NavMesh`
		Unk4D,					 // 0x4D TLOD X
		Topic,					 // 0x4E DIAL X `TESTopic`
		TopicInfo,				 // 0x4F INFO X `TESTopicInfo`
		Quest,					 // 0x50 QUST X `TESQuest`
		Idle,					 // 0x51 IDLE X `TESIdleForm`
		Package,				 // 0x52 PACK X `TESPackage`
								 //           X `AlarmPackage`
								 //           X `DialoguePackage`
								 //           X `FleePackage`
								 //           X `SpectatorPackage`
								 //           X `TrespassPackage`
		CombatStyle,			 // 0x53 CSTY X `TESCombatStyle`
		LoadScreen,				 // 0x54 LSCR X `TESLoadScreen`
		LeveledSpell,			 // 0x55 LVSP X `TESLevSpell`
		AnimObject,				 // 0x56 ANIO X `TESObjectANIO`
		WaterType,				 // 0x57 WATR X `TESWaterForm`
		EffectShader,			 // 0x58 EFSH X `TESEffectShader`
		OffsetTable,			 // 0x59 TOFT X
		Explosion,				 // 0x5A EXPL X `BGSExplosion`
		Debris,					 // 0x5B DEBR X `BGSDebris`
		ImageSpace,				 // 0x5C IMGS X `TESImageSpace`
		ImageSpaceModifier,		 // 0x5D IMAD X `TESImageSpaceModifier`
		FormList,				 // 0x5E FLST X `BGSListForm`
		Perk,					 // 0x5F PERK X `BGSPerk`
		BodyPartData,			 // 0x60 BPTD X `BGSBodyPartData`
		AddonNode,				 // 0x61 ADDN X `BGSAddonNode`
		ActorValue,				 // 0x62 AVIF X `ActorValueInfo`
		CameraShot,				 // 0x63 CAMS X `BGSCameraShot`
		CameraPath,				 // 0x64 CPTH X `BGSCameraPath`
		VoiceType,				 // 0x65 VTYP X `BGSVoiceType`
		MaterialType,			 // 0x66 MATT X `BGSMaterialType`
		ImpactData,				 // 0x67 IPCT X `BGSImpactData`
		ImpactDataSet,			 // 0x68 IPDS X `BGSImpactDataSet`
		ArmorAddon,				 // 0x69 ARMA X `TESObjectARMA`
		EncounterZone,			 // 0x6A ECZN X `BGSEncounterZone`
		Location,				 // 0x6B LCTN X `BGSLocation`
		Message,				 // 0x6C MESG X `BGSMessage`
		Ragdoll,				 // 0x6D RGDL X
		DefaultObjectManager,	 // 0x6E DOBJ X `BGSDefaultObjectManager`
		DefaultObject,			 // 0x6F DFOB X `BGSDefaultObject`
		LightingTemplate,		 // 0x70 LGTM X `BGSLightingTemplate`
		MusicType,				 // 0x71 MUSC X `BGSMusicType`
		Footstep,				 // 0x72 FSTP X `BGSFootstep`
		FootstepSet,			 // 0x73 FSTS X `BGSFootstepSet`
		StoryManagerBranchNode,	 // 0x74 SMBN X `BGSStoryManagerBranchNode`
		StoryManagerQuestNode,	 // 0x75 SMQN X `BGSStoryManagerQuestNode`
		StoryManagerEventNode,	 // 0x76 SMEN X `BGSStoryManagerEventNode`
		DialogueBranch,			 // 0x77 DLBR X `BGSDialogueBranch`
		MusicTrack,				 // 0x78 MUST X `BGSMusicTrackFormWrapper`
		DialogueView,			 // 0x79 DLVW X
		WordOfPower,			 // 0x7A WOOP X `TESWordOfPower`
		Shout,					 // 0x7B SHOU X `TESShout`
		EquipSlot,				 // 0x7C EQUP X `BGSEquipSlot`
		Relationship,			 // 0x7D RELA X `BGSRelationship`
		Scene,					 // 0x7E SCEN X `BGSScene`
		AssociationType,		 // 0x7F ASTP X `BGSAssociationType`
		Outfit,					 // 0x80 OTFT X `BGSOutfit`
		ArtObject,				 // 0x81 ARTO X `BGSArtObject`
		MaterialObject,			 // 0x82 MATO X `BGSMaterialObject`
		MovementType,			 // 0x83 MOVT X `BGSMovementType`
		SoundDescriptor,		 // 0x84 SNDR X `BGSSoundDescriptorForm`
		DualCastData,			 // 0x85 DUAL X `BGSDualCastData`
		SoundCategory,			 // 0x86 SNCT X `BGSSoundCategory`
		SoundOutput,			 // 0x87 SOPM X `BGSSoundOutput`
		CollisionLayer,			 // 0x88 COLL X `BGSCollisionLayer`
		ColorForm,				 // 0x89 CLFM X `BGSColorForm`
		ReverbParameters,		 // 0x8A REVB X `BGSReverbParameters`
		PackIn,					 // 0x8B PKIN X `BGSPackIn`
		ReferenceGroup,			 // 0x8C RFGP X `BGSReferenceGroup`
		AimModel,				 // 0x8D AMDL X `BGSAimModel`
		Layer,					 // 0x8E LAYR X
		ConstructibleObject,	 // 0x8F COBJ X `BGSConstructibleObject`
		ObjectMod,				 // 0x90 OMOD X `BGSMod::Attachment::Mod`
		MaterialSwap,			 // 0x91 MSWP X `BGSMaterialSwap`
		ZoomData,				 // 0x92 ZOOM X `BGSZoomData`
		InstanceNamingRules,	 // 0x93 INNR X `BGSInstanceNamingRules`
		SoundKeywordMapping,	 // 0x94 KSSM X `BGSSoundKeywordMapping`
		AudioEffectChain,		 // 0x95 AECH X `BGSAudioEffectChain`
		SceneCollection,		 // 0x96 SCCO X
		AttractionRule,			 // 0x97 AORU X `BGSAttractionRule`
		SoundCategorySnapshot,	 // 0x98 SCSN X `BGSSoundCategorySnapshot`
		SoundTagSet,			 // 0x99 STAG X `BGSSoundTagSet`
		NavMeshObstacleManager,	 // 0x9A NOCM X `NavMeshObstacleCoverManager`
		LensFlare,				 // 0x9B LENS X `BGSLensFlare`
		LensSprite,				 // 0x9C LSPR X
		GodRays,				 // 0x9D GDRY X `BGSGodRays`
		ObjectVisibilityManager, // 0x9E OVIS X `BGSObjectVisibilityManager`

		_Count, // 0x9F

		BaseAlias,			// 0xA0 X `BGSBaseAlias`
		RefAlias,			// 0xA1 X `BGSRefAlias`
		LocationAlias,		// 0xA2 X `BGSLocAlias`
		ActiveEffect,		// 0xA3 X `ActiveEffect`
		InputEnableLayer,	// 0xA4 X `BSInputEnableLayer`
		RefCollectionAlias, // 0xA5 X `BGSRefCollectionAlias`

		ScriptObject = -1, // 0xFFFFFFFF X `BSScript::Object`

		_Min = None,
		_Max = ObjectVisibilityManager
	};
}
