#pragma once

#include "RE/B/BGSAttachParentArray.hpp"
#include "RE/B/BGSBlockBashData.hpp"
#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSEquipType.hpp"
#include "RE/B/BGSInstanceNamingRulesForm.hpp"
#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSMessageIcon.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSPickupPutdownSounds.hpp"
#include "RE/B/BGSPreloadable.hpp"
#include "RE/B/BGSTypedFormValuePair.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/M/MELEE_ATTACK_SPEED.hpp"
#include "RE/T/TBO_InstanceData.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESEnchantableForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESIcon.hpp"
#include "RE/W/WEAPON_FLAGS.hpp"
#include "RE/W/WEAPON_TYPE.hpp"

namespace RE
{
	enum class SOUND_LEVEL : std::int32_t;
	enum class STAGGER_MAGNITUDE : std::int32_t;
	enum class WEAPON_RUMBLE_PATTERN : std::int32_t;
	enum class WEAPONHITBEHAVIOR : std::int32_t;

	class __declspec(novtable) TESObjectWEAP
		: public TESBoundObject,			// 000
		  public TESFullName,				// 068
		  public BGSModelMaterialSwap,		// 078
		  public TESIcon,					// 0B8
		  public TESEnchantableForm,		// 0C8
		  public BGSDestructibleObjectForm, // 0E0
		  public BGSEquipType,				// 0F0
		  public BGSPreloadable,			// 100
		  public BGSMessageIcon,			// 108
		  public BGSPickupPutdownSounds,	// 120
		  public BGSBlockBashData,			// 138
		  public BGSKeywordForm,			// 150
		  public TESDescription,			// 170
		  public BGSInstanceNamingRulesForm // 188
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectWEAP };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectWEAP };
		inline static constexpr auto FORM_TYPE{ FormType::kWeapon };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kNonPlayable = 1 << 2,
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class RangedData
		{
		public:
			// members
			BGSProjectile* overrideProjectile;							  // 00
			REX::Float32 fireSeconds;									  // 08
			REX::Float32 firingRumbleLeftMotorStrength;					  // 0C
			REX::Float32 firingRumbleRightMotorStrength;				  // 10
			REX::Float32 firingRumbleDuration;							  // 14
			REX::Float32 reloadSeconds;									  // 18
			REX::Float32 boltChargeSeconds;								  // 1C
			REX::Float32 sightedTransitionSeconds;						  // 20
			std::uint32_t rumblePeriod;									  // 24
			REX::Enum<WEAPON_RUMBLE_PATTERN, std::int32_t> rumblePattern; // 28
			std::uint8_t numProjectiles;								  // 2C
		};
		static_assert(sizeof(RangedData) == 0x30);

		class __declspec(novtable) InstanceData
			: public TBO_InstanceData // 00
		{
		public:
			inline static constexpr auto RTTI{ RTTI::TESObjectWEAP__InstanceData };
			inline static constexpr auto VTABLE{ VTABLE::TESObjectWEAP__InstanceData };

			~InstanceData() override; // 00

			// members
			BGSSoundDescriptorForm* attackSound;										// 010
			BGSSoundDescriptorForm* attackSound2D;										// 018
			BGSSoundDescriptorForm* attackLoop;											// 020
			BGSSoundDescriptorForm* attackFailSound;									// 028
			BGSSoundDescriptorForm* idleSound;											// 030
			BGSSoundDescriptorForm* equipSound;											// 038
			BGSSoundDescriptorForm* unEquipSound;										// 040
			BGSSoundDescriptorForm* fastEquipSound;										// 048
			BGSBlockBashData* blockBashData;											// 050
			BGSImpactDataSet* impactDataSet;											// 058
			TESLevItem* npcAddAmmoList;													// 060
			TESAmmo* ammo;																// 068
			BGSEquipSlot* equipSlot;													// 070
			SpellItem* effect;															// 078
			BGSKeywordForm* keywords;													// 080
			BGSAimModel* aimModel;														// 088
			BGSZoomData* zoomData;														// 090
			RangedData* rangedData;														// 098
			BSTArray<EnchantmentItem*>* enchantments;									// 0A0
			BSTArray<BGSMaterialSwap*>* materialSwaps;									// 0A8
			BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* damageTypes; // 0B0
			BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* actorValues; // 0B8
			REX::Float32 attackSeconds;													// 0C0
			REX::Float32 reloadSpeed;													// 0C4
			REX::Float32 speed;															// 0C8
			REX::Float32 reach;															// 0CC
			REX::Float32 minRange;														// 0D0
			REX::Float32 maxRange;														// 0D4
			REX::Float32 attackDelaySec;												// 0D8
			REX::Float32 damageToWeaponMult;											// 0DC
			REX::Float32 outOfRangeDamageMult;											// 0E0
			REX::Float32 secondaryDamage;												// 0E4
			REX::Float32 criticalChargeBonus;											// 0E8
			REX::Float32 weight;														// 0EC
			REX::Float32 soundLevelMult;												// 0F0
			REX::Float32 attackActionPointCost;											// 0F4
			REX::Float32 fullPowerSeconds;												// 0F8
			REX::Float32 minPowerPerShot;												// 0FC
			REX::Float32 colorRemappingIndex;											// 100
			REX::Float32 criticalDamageMult;											// 104
			REX::Enum<STAGGER_MAGNITUDE, std::int32_t> staggerValue;					// 108
			std::uint32_t value;														// 10C
			REX::EnumSet<WEAPON_FLAGS, std::uint32_t> flags;							// 110
			REX::Enum<SOUND_LEVEL, std::int32_t> soundLevel;							// 114
			REX::Enum<WEAPONHITBEHAVIOR, std::int32_t> hitBehavior;						// 118
			ActorValueInfo* skill;														// 120
			ActorValueInfo* resistance;													// 128
			std::uint16_t ammoCapacity;													// 130
			std::uint16_t attackDamage;													// 132
			std::uint16_t rank;															// 134
			std::uint8_t accuracyBonus;													// 136
			REX::Enum<WEAPON_TYPE, std::int8_t> type;									// 137
		};
		static_assert(sizeof(InstanceData) == 0x138);

		class __declspec(novtable) Data
			: public InstanceData // 00
		{
		public:
			inline static constexpr auto RTTI{ RTTI::TESObjectWEAP__Data };
			inline static constexpr auto VTABLE{ VTABLE::TESObjectWEAP__Data };

			~Data() override; // 00
		};
		static_assert(sizeof(Data) == 0x138);

		[[nodiscard]] MELEE_ATTACK_SPEED GetMeleeAttackSpeed() const
		{
			using FuncType = decltype(&TESObjectWEAP::GetMeleeAttackSpeed);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectWEAP::GetMeleeAttackSpeed };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] static const char* GetMeleeAttackSpeedLabel(MELEE_ATTACK_SPEED a_speed)
		{
			using FuncType = decltype(&TESObjectWEAP::GetMeleeAttackSpeedLabel);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectWEAP::GetMeleeAttackSpeedLabel };
			return std::invoke(FUNC, a_speed);
		}

		[[nodiscard]] REX::Float32 GetShotsPerSecond(InstanceData* a_instanceData) const
		{
			using FuncType = decltype(&TESObjectWEAP::GetShotsPerSecond);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectWEAP::GetShotsPerSecond };
			return std::invoke(FUNC, this, a_instanceData);
		}

		[[nodiscard]] bool IsMeleeWeapon() const noexcept
		{
			return weaponData.type.any(
				WEAPON_TYPE::kOneHandSword,
				WEAPON_TYPE::kOneHandDagger,
				WEAPON_TYPE::kOneHandAxe,
				WEAPON_TYPE::kOneHandMace,
				WEAPON_TYPE::kTwoHandSword,
				WEAPON_TYPE::kTwoHandAxe);
		}

		[[nodiscard]] bool IsGunWeapon() const noexcept
		{
			return weaponData.type.any(
				WEAPON_TYPE::kGun);
		}

		[[nodiscard]] bool IsThrownWeapon() const
		{
			return weaponData.type.any(
				WEAPON_TYPE::kGrenade,
				WEAPON_TYPE::kMine);
		}

		[[nodiscard]] bool IsOneHandedWeapon() const noexcept
		{
			return weaponData.type.any(
				WEAPON_TYPE::kOneHandSword,
				WEAPON_TYPE::kOneHandDagger,
				WEAPON_TYPE::kOneHandAxe,
				WEAPON_TYPE::kOneHandMace);
		}

		[[nodiscard]] bool IsTwoHandedWeapon() const noexcept
		{
			return weaponData.type.any(
				WEAPON_TYPE::kTwoHandSword,
				WEAPON_TYPE::kTwoHandAxe);
		}

		[[nodiscard]] bool IsRangedWeapon() const noexcept
		{
			return weaponData.type.any(
				WEAPON_TYPE::kBow,
				WEAPON_TYPE::kStaff,
				WEAPON_TYPE::kGun,
				WEAPON_TYPE::kGrenade,
				WEAPON_TYPE::kMine);
		}

		[[nodiscard]] bool IsBoundWeapon() const noexcept
		{
			return weaponData.flags.all(
				WEAPON_FLAGS::kBoundWeapon);
		}

		[[nodiscard]] bool IsEmbeddedWeapon() const noexcept
		{
			return weaponData.flags.all(
				WEAPON_FLAGS::kEmbeddedWeapon);
		}

		// members
		TESObjectWEAP::Data weaponData;				// 198
		BGSModelMaterialSwap* firstPersonModel;		// 2D0
		TESObjectWEAP* weaponTemplate;				// 2D8
		BGSMod::Attachment::Mod* embeddedWeaponMod; // 2E0
		BGSAttachParentArray attachParents;			// 2E8
	};
	static_assert(sizeof(TESObjectWEAP) == 0x300);
}
