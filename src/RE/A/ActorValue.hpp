#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"

namespace RE
{
	class ActorValue : public BSTSingletonImplicit<ActorValue> // 0x00
	{
	public:
		enum class AVType : std::int32_t
		{
			DerivedAttribute = 0,
			Attribute = 1,
			Skill = 2,
			AIAttribute = 3,
			Resistance = 4,
			Condition = 5,
			Charge = 6,
			IntValue = 7,
			Variable = 8,
			Resource = 9,

			_Count = 10
		};

		enum class Flags : std::uint32_t
		{
			None = 0,
			Depreciated = 1 << 1,
			Enumeration = 1 << 2,
			NoScriptModAV = 1 << 3,
			Cache = 1 << 4,
			CachePermenant = 1 << 5,
			AlwaysClamp = 1 << 6,
			ImplicitBase0 = 1 << 10,
			ImplicitBase1 = 1 << 11,
			ImplicitBase100 = 1 << 12,
			UserDefined = 1 << 13,
			Derived = 1 << 15,
			BaseUseAutoCalc = 1 << 16,
			Min1 = 1 << 20,
			Max10 = 1 << 21,
			Max100 = 1 << 22,
			ScaleBy100 = 1 << 23,
			Percentage = 1 << 24,
			DamageMinZero = 1 << 25,
			DamageIsPositive = 1 << 26,
			GodModeNoDamage = 1 << 27,
			DoesNotRecover = 1 << 28,
			Hardcoded = static_cast<std::uint32_t>(1) << 31
		};

		[[nodiscard]]
		static auto GetSingleton() -> ActorValue*
		{
			using FuncType = decltype(&ActorValue::GetSingleton);
			static const auto FUNC = REL::Relocation<FuncType>(ID::ActorValue::Singleton);
			return std::invoke(FUNC);
		}

		// members
		ActorValueInfo* absorbChance;												// 0x000
		ActorValueInfo* actionPoints;												// 0x008
		ActorValueInfo* aggression;													// 0x010
		ActorValueInfo* agility;													// 0x018
		ActorValueInfo* aimStability;												// 0x020
		ActorValueInfo* alchemy;													// 0x028
		ActorValueInfo* animationMult;												// 0x030
		ActorValueInfo* armorPerks;													// 0x038
		ActorValueInfo* assistance;													// 0x040
		ActorValueInfo* attackDamageMult;											// 0x048
		ActorValueInfo* blindness;													// 0x050
		ActorValueInfo* block;														// 0x058
		ActorValueInfo* bloodyMess;													// 0x060
		ActorValueInfo* bowSpeedBonus;												// 0x068
		ActorValueInfo* bowStaggerBonus;											// 0x070
		ActorValueInfo* brainCondition;												// 0x078
		ActorValueInfo* carryWeight;												// 0x080
		ActorValueInfo* charisma;													// 0x088
		ActorValueInfo* combatHealthRegenMult;										// 0x090
		ActorValueInfo* confidence;													// 0x098
		ActorValueInfo* criticalChance;												// 0x0A0
		ActorValueInfo* damageResistance;											// 0x0A8
		ActorValueInfo* deafness;													// 0x0B0
		ActorValueInfo* enchanting;													// 0x0B8
		ActorValueInfo* endurance;													// 0x0C0
		ActorValueInfo* enduranceCondition;											// 0x0C8
		ActorValueInfo* experience;													// 0x0D0
		ActorValueInfo* health;														// 0x0D8
		ActorValueInfo* healRateMult;												// 0x0E0
		ActorValueInfo* idleChatterTimeMin;											// 0x0E8
		ActorValueInfo* idleChatterTimeMAx;											// 0x0F0
		ActorValueInfo* ignoreCrippledLimbs;										// 0x0F8
		ActorValueInfo* intelligence;												// 0x100
		ActorValueInfo* invisibility;												// 0x108
		ActorValueInfo* karma;														// 0x110
		ActorValueInfo* leftAttackCondition;										// 0x118
		ActorValueInfo* leftItemCharge;												// 0x120
		ActorValueInfo* leftMobiltyCondition;										// 0x128
		ActorValueInfo* leftWeaponSpeedMult;										// 0x130
		ActorValueInfo* lockpicking;												// 0x138
		ActorValueInfo* luck;														// 0x140
		ActorValueInfo* mass;														// 0x148
		ActorValueInfo* meleeDamage;												// 0x150
		ActorValueInfo* morality;													// 0x158
		ActorValueInfo* movementNoiseMult;											// 0x160
		ActorValueInfo* nightEyeBonus;												// 0x168
		ActorValueInfo* perception;													// 0x170
		ActorValueInfo* perceptionCondition;										// 0x178
		ActorValueInfo* pickpocket;													// 0x180
		ActorValueInfo* poisonResistance;											// 0x188
		ActorValueInfo* powerArmorBattery;											// 0x190
		ActorValueInfo* powerArmorHeadCondition;									// 0x198
		ActorValueInfo* powerArmorTorsoCondition;									// 0x1A0
		ActorValueInfo* powerArmorLeftArmCondition;									// 0x1A8
		ActorValueInfo* powerArmorRightArmCondition;								// 0x1B0
		ActorValueInfo* powerArmorLeftLegCondition;									// 0x1B8
		ActorValueInfo* powerArmorRightLegCondition;								// 0x1C0
		ActorValueInfo* radHealthMax;												// 0x1C8
		ActorValueInfo* rads;														// 0x1D0
		ActorValueInfo* fatigueAPMax;												// 0x1D8
		ActorValueInfo* fatigue;													// 0x1E0
		ActorValueInfo* reflectDamage;												// 0x1E8
		ActorValueInfo* restoreConditionRate;										// 0x1F0
		ActorValueInfo* rightAttackCondition;										// 0x1F8
		ActorValueInfo* rightItemCharge;											// 0x200
		ActorValueInfo* rightMobilityCondition;										// 0x208
		ActorValueInfo* rotationSpeedCondition;										// 0x210
		ActorValueInfo* shieldPerks;												// 0x218
		ActorValueInfo* shoutRecoveryMult;											// 0x220
		ActorValueInfo* sneak;														// 0x228
		ActorValueInfo* speechcraft;												// 0x230
		ActorValueInfo* speedMult;													// 0x238
		ActorValueInfo* stamina;													// 0x240
		ActorValueInfo* strength;													// 0x248
		ActorValueInfo* suspicious;													// 0x250
		ActorValueInfo* telekinesis;												// 0x258
		ActorValueInfo* unarmedDamage;												// 0x260
		ActorValueInfo* vansPerk;													// 0x268
		ActorValueInfo* wardPower;													// 0x270
		ActorValueInfo* waitingForPlayer;											// 0x278
		ActorValueInfo* waterBreathing;												// 0x280
		ActorValueInfo* waterWalking;												// 0x288
		ActorValueInfo* weaponSpeedMult;											// 0x290
		ActorValueInfo* weapReloadSpeedMult;										// 0x298
		ActorValueInfo* restoreHealthRate;											// 0x2A0
		ActorValueInfo* restoreAPRate;												// 0x2A8
		ActorValueInfo* apRateMult;													// 0x2B0
		ActorValueInfo* restoreRadsRate;											// 0x2B8
		ActorValueInfo* radsRateMult;												// 0x2C0
		ActorValueInfo* restoreFatigueRate;											// 0x2C8
		ActorValueInfo* fatigueRateMult;											// 0x2D0
		ActorValueInfo* conditionRateMult;											// 0x2D8
		ActorValueInfo* fireResistance;												// 0x2E0
		ActorValueInfo* electricalResistance;										// 0x2E8
		ActorValueInfo* frostResistance;											// 0x2F0
		ActorValueInfo* magicResistance;											// 0x2F8
		ActorValueInfo* radIngestionResistance;										// 0x300
		ActorValueInfo* radExposureResistance;										// 0x308
		ActorValueInfo* energy;														// 0x310
		ActorValueInfo* energyResistance;											// 0x318
		ActorValueInfo* paralysis;													// 0x320
		ActorValueInfo* attackConditionAlt01;										// 0x328
		ActorValueInfo* attackConditionAlt02;										// 0x330
		ActorValueInfo* attackConditionAlt03;										// 0x338
		ActorValueInfo* powerGenerated;												// 0x340
		ActorValueInfo* powerRadation;												// 0x348
		ActorValueInfo* powerRequired;												// 0x350
		ActorValueInfo* resourceFood;												// 0x358
		ActorValueInfo* resourceWater;												// 0x360
		ActorValueInfo* resourceSafety;												// 0x368
		ActorValueInfo* resourceBed;												// 0x370
		ActorValueInfo* resourceHappiness;											// 0x378
		ActorValueInfo* resourceArtillery;											// 0x380
		ActorValueInfo* workshopItemOverlap;										// 0x388
		ActorValueInfo* workshopItemClampDirection;									// 0x390
		ActorValueInfo* workshopItemZOffset;										// 0x398
		ActorValueInfo* workshopPlayerOwned;										// 0x3A0
		ActorValueInfo* workshopActorWounded;										// 0x3A8
		ActorValueInfo* workshopStackableItem;										// 0x3B0
		ActorValueInfo* workshopSnapPointRadius;									// 0x3B8
		ActorValueInfo* workshopAnythingIsGround;									// 0x3C0
		ActorValueInfo* workshopMaxTriangles;										// 0x3C8
		ActorValueInfo* workshopMaxDraws;											// 0x3D0
		ActorValueInfo* workshopCurrentTriangles;									// 0x3D8
		ActorValueInfo* workshopCurrentDraws;										// 0x3E0
		ActorValueInfo* workshopIgnoreSimpleIntersections;							// 0x3E8
		ActorValueInfo* workshopAllowUnsupportedStacking;							// 0x3F0
		ActorValueInfo* workshopSnapTransmitsPower;									// 0x3F8
		ActorValueInfo* workshopPowerConnection;									// 0x400
		ActorValueInfo* logicOperation;												// 0x408
		ActorValueInfo* logicOutput;												// 0x410
		ActorValueInfo* ignorePlayerWhileFrenzied;									// 0x418
		BSTArray<ActorValueInfo*> hardcodedActorValues;								// 0x420
		BSTArray<ActorValueInfo*> conditionActorValues;								// 0x438
		std::array<std::uint32_t, std::to_underlying(AVType::_Count)> avTypeCounts; // 0x450
	};

	static_assert(sizeof(ActorValue) == 0x478);
}
