#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSString.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"
#include "RE/Bethesda/FormComponents.hpp"
#include "RE/Bethesda/TESForms.hpp"

namespace RE
{
	class ActorValueOwner;

	class ActorValue
		: public BSTSingletonImplicit<ActorValue> // 000
	{
	public:
		enum class AVType
		{
			kDerivedAttribute,
			kAttribute,
			kSkill,
			kAIAttribute,
			kResistance,
			kCondition,
			kCharge,
			kIntValue,
			kVariable,
			kResource
		};

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kDepreciated = 1u << 1,
			kEnumeration = 1u << 2,
			kNoScriptModAV = 1u << 3,
			kCache = 1u << 4,
			kCachePermenant = 1u << 5,
			kAlwaysClamp = 1u << 6,
			kImplicitBase0 = 1u << 10,
			kImplicitBase1 = 1u << 11,
			kImplicitBase100 = 1u << 12,
			kUserDefined = 1u << 13,
			kDerived = 1u << 15,
			kBaseUseAutoCalc = 1u << 16,
			kMin1 = 1u << 20,
			kMax10 = 1u << 21,
			kMax100 = 1u << 22,
			kScaleBy100 = 1u << 23,
			kPercentage = 1u << 24,
			kDamageMinZero = 1u << 25,
			kDamageIsPositive = 1u << 26,
			kGodModeNoDamage = 1u << 27,
			kDoesNotRecover = 1u << 28,
			kHardcoded = 1u << 31,
		};

		[[nodiscard]] static ActorValue* GetSingleton()
		{
			using func_t = decltype(&ActorValue::GetSingleton);
			static REL::Relocation<func_t> func{ REL::RelocationID(405390, 2189587) };
			return func();
		}

		// members
		ActorValueInfo* absorbChance;					   // 000
		ActorValueInfo* actionPoints;					   // 008
		ActorValueInfo* aggression;						   // 010
		ActorValueInfo* agility;						   // 018
		ActorValueInfo* aimStability;					   // 020
		ActorValueInfo* alchemy;						   // 028
		ActorValueInfo* animationMult;					   // 030
		ActorValueInfo* armorPerks;						   // 038
		ActorValueInfo* assistance;						   // 040
		ActorValueInfo* attackDamageMult;				   // 048
		ActorValueInfo* blindness;						   // 050
		ActorValueInfo* block;							   // 058
		ActorValueInfo* bloodyMess;						   // 060
		ActorValueInfo* bowSpeedBonus;					   // 068
		ActorValueInfo* bowStaggerBonus;				   // 070
		ActorValueInfo* brainCondition;					   // 078
		ActorValueInfo* carryWeight;					   // 080
		ActorValueInfo* charisma;						   // 088
		ActorValueInfo* combatHealthRegenMult;			   // 090
		ActorValueInfo* confidence;						   // 098
		ActorValueInfo* criticalChance;					   // 0A0
		ActorValueInfo* damageResistance;				   // 0A8
		ActorValueInfo* deafness;						   // 0B0
		ActorValueInfo* enchanting;						   // 0B8
		ActorValueInfo* endurance;						   // 0C0
		ActorValueInfo* enduranceCondition;				   // 0C8
		ActorValueInfo* experience;						   // 0D0
		ActorValueInfo* health;							   // 0D8
		ActorValueInfo* healRateMult;					   // 0E0
		ActorValueInfo* idleChatterTimeMin;				   // 0E8
		ActorValueInfo* idleChatterTimeMAx;				   // 0F0
		ActorValueInfo* ignoreCrippledLimbs;			   // 0F8
		ActorValueInfo* intelligence;					   // 100
		ActorValueInfo* invisibility;					   // 108
		ActorValueInfo* karma;							   // 110
		ActorValueInfo* leftAttackCondition;			   // 118
		ActorValueInfo* leftItemCharge;					   // 120
		ActorValueInfo* leftMobiltyCondition;			   // 128
		ActorValueInfo* leftWeaponSpeedMult;			   // 130
		ActorValueInfo* lockpicking;					   // 138
		ActorValueInfo* luck;							   // 140
		ActorValueInfo* mass;							   // 148
		ActorValueInfo* meleeDamage;					   // 150
		ActorValueInfo* morality;						   // 158
		ActorValueInfo* movementNoiseMult;				   // 160
		ActorValueInfo* nightEyeBonus;					   // 168
		ActorValueInfo* perception;						   // 170
		ActorValueInfo* perceptionCondition;			   // 178
		ActorValueInfo* pickpocket;						   // 180
		ActorValueInfo* poisonResistance;				   // 188
		ActorValueInfo* powerArmorBattery;				   // 190
		ActorValueInfo* powerArmorHeadCondition;		   // 198
		ActorValueInfo* powerArmorTorsoCondition;		   // 1A0
		ActorValueInfo* powerArmorLeftArmCondition;		   // 1A8
		ActorValueInfo* powerArmorRightArmCondition;	   // 1B0
		ActorValueInfo* powerArmorLeftLegCondition;		   // 1B8
		ActorValueInfo* powerArmorRightLegCondition;	   // 1C0
		ActorValueInfo* radHealthMax;					   // 1C8
		ActorValueInfo* rads;							   // 1D0
		ActorValueInfo* fatigueAPMax;					   // 1D8
		ActorValueInfo* fatigue;						   // 1E0
		ActorValueInfo* reflectDamage;					   // 1E8
		ActorValueInfo* restoreConditionRate;			   // 1F0
		ActorValueInfo* rightAttackCondition;			   // 1F8
		ActorValueInfo* rightItemCharge;				   // 200
		ActorValueInfo* rightMobilityCondition;			   // 208
		ActorValueInfo* rotationSpeedCondition;			   // 210
		ActorValueInfo* shieldPerks;					   // 218
		ActorValueInfo* shoutRecoveryMult;				   // 220
		ActorValueInfo* sneak;							   // 228
		ActorValueInfo* speechcraft;					   // 230
		ActorValueInfo* speedMult;						   // 238
		ActorValueInfo* stamina;						   // 240
		ActorValueInfo* strength;						   // 248
		ActorValueInfo* suspicious;						   // 250
		ActorValueInfo* telekinesis;					   // 258
		ActorValueInfo* unarmedDamage;					   // 260
		ActorValueInfo* vansPerk;						   // 268
		ActorValueInfo* wardPower;						   // 270
		ActorValueInfo* waitingForPlayer;				   // 278
		ActorValueInfo* waterBreathing;					   // 280
		ActorValueInfo* waterWalking;					   // 288
		ActorValueInfo* weaponSpeedMult;				   // 290
		ActorValueInfo* weapReloadSpeedMult;			   // 298
		ActorValueInfo* restoreHealthRate;				   // 2A0
		ActorValueInfo* restoreAPRate;					   // 2A8
		ActorValueInfo* apRateMult;						   // 2B0
		ActorValueInfo* restoreRadsRate;				   // 2B8
		ActorValueInfo* radsRateMult;					   // 2C0
		ActorValueInfo* restoreFatigueRate;				   // 2C8
		ActorValueInfo* fatigueRateMult;				   // 2D0
		ActorValueInfo* conditionRateMult;				   // 2D8
		ActorValueInfo* fireResistance;					   // 2E0
		ActorValueInfo* electricalResistance;			   // 2E8
		ActorValueInfo* frostResistance;				   // 2F0
		ActorValueInfo* magicResistance;				   // 2F8
		ActorValueInfo* radIngestionResistance;			   // 300
		ActorValueInfo* radExposureResistance;			   // 308
		ActorValueInfo* energy;							   // 310
		ActorValueInfo* energyResistance;				   // 318
		ActorValueInfo* paralysis;						   // 320
		ActorValueInfo* attackConditionAlt1;			   // 328
		ActorValueInfo* attackConditionAlt2;			   // 330
		ActorValueInfo* attackConditionAlt3;			   // 338
		ActorValueInfo* powerGenerated;					   // 340
		ActorValueInfo* powerRadation;					   // 348
		ActorValueInfo* powerRequired;					   // 350
		ActorValueInfo* resourceFood;					   // 358
		ActorValueInfo* resourceWater;					   // 360
		ActorValueInfo* resourceSafety;					   // 368
		ActorValueInfo* resourceBed;					   // 370
		ActorValueInfo* resourceHappiness;				   // 378
		ActorValueInfo* resourceArtillery;				   // 380
		ActorValueInfo* workshopItemOverlap;			   // 388
		ActorValueInfo* workshopItemClampDirection;		   // 390
		ActorValueInfo* workshopItemZOffset;			   // 398
		ActorValueInfo* workshopPlayerOwned;			   // 3A0
		ActorValueInfo* workshopActorWounded;			   // 3A8
		ActorValueInfo* workshopStackableItem;			   // 3B0
		ActorValueInfo* workshopSnapPointRadius;		   // 3B8
		ActorValueInfo* workshopAnythingIsGround;		   // 3C0
		ActorValueInfo* workshopMaxTriangles;			   // 3C8
		ActorValueInfo* workshopMaxDraws;				   // 3D0
		ActorValueInfo* workshopCurrentTriangles;		   // 3D8
		ActorValueInfo* workshopCurrentDraws;			   // 3E0
		ActorValueInfo* workshopIgnoreSimpleIntersections; // 3E8
		ActorValueInfo* workshopAllowUnsupportedStacking;  // 3F0
		ActorValueInfo* workshopSnapTransmitsPower;		   // 3F8
		ActorValueInfo* workshopPowerConnection;		   // 400
		ActorValueInfo* logicOperation;					   // 408
		ActorValueInfo* logicOutput;					   // 410
		ActorValueInfo* ignorePlayerWhileFrenzied;		   // 418
		BSTArray<ActorValueInfo*> hardcodedActorValues;	   // 420
		BSTArray<ActorValueInfo*> conditionActorValues;	   // 438
		std::uint32_t avTypeCounts[10];					   // 450
	};
	static_assert(sizeof(ActorValue) == 0x478);

	class __declspec(novtable) ActorValueInfo
		: public TESForm,		// 000
		  public TESFullName,	// 020
		  public TESDescription // 030
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ActorValueInfo };
		inline static constexpr auto VTABLE{ VTABLE::ActorValueInfo };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kAVIF };

		using ModifiedCallback_t = void(Actor* a_actor, const ActorValueInfo& a_info, float a_originalValue, float a_delta, Actor* a_actorSource);
		using DerivationFunction_t = float(const ActorValueOwner* a_actor, const ActorValueInfo& a_info);

		// members
		std::function<ModifiedCallback_t> modifiedCallback;		// 048
		BSString formEditorID;									// 088
		ActorValueInfo* dependentActorValues[15];				// 098
		std::function<DerivationFunction_t> derivationFunction; // 110
		const char* enumNames[10];								// 150
		BGSLocalizedString abbreviation;						// 1A0
		std::int32_t oldActorValue;								// 1A8
		REX::EnumSet<ActorValue::Flags, std::uint32_t> flags;	// 1AC
		REX::Enum<ActorValue::AVType, std::uint32_t> avType;	// 1B0
		std::uint32_t numDependentActorValues;					// 1B4
		std::uint32_t enumCount;								// 1B8
		std::int32_t fullCacheIndex;							// 1BC
		std::int32_t permanentCacheIndex;						// 1C0
		float defaultValue;										// 1C4
		std::uint32_t sortIndex;								// 1C8
	};
	static_assert(sizeof(ActorValueInfo) == 0x1D0);
}
