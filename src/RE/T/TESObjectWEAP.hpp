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

	class __declspec(novtable) TESObjectWEAP :
		public TESBoundObject,			  // 0x000
		public TESFullName,				  // 0x068
		public BGSModelMaterialSwap,	  // 0x078
		public TESIcon,					  // 0x0B8
		public TESEnchantableForm,		  // 0x0C8
		public BGSDestructibleObjectForm, // 0x0E0
		public BGSEquipType,			  // 0x0F0
		public BGSPreloadable,			  // 0x100
		public BGSMessageIcon,			  // 0x108
		public BGSPickupPutdownSounds,	  // 0x120
		public BGSBlockBashData,		  // 0x138
		public BGSKeywordForm,			  // 0x150
		public TESDescription,			  // 0x170
		public BGSInstanceNamingRulesForm // 0x188
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectWEAP;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectWEAP;
		inline static constexpr auto FORM_TYPE = FormType::Weapon;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				NonPlayable = 1 << 2,
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class RangedData
		{
		public:
			// members
			BGSProjectile* overrideProjectile;							  // 0x00
			REX::Float32 fireSeconds;									  // 0x08
			REX::Float32 firingRumbleLeftMotorStrength;					  // 0x0C
			REX::Float32 firingRumbleRightMotorStrength;				  // 0x10
			REX::Float32 firingRumbleDuration;							  // 0x14
			REX::Float32 reloadSeconds;									  // 0x18
			REX::Float32 boltChargeSeconds;								  // 0x1C
			REX::Float32 sightedTransitionSeconds;						  // 0x20
			std::uint32_t rumblePeriod;									  // 0x24
			REX::Enum<WEAPON_RUMBLE_PATTERN, std::int32_t> rumblePattern; // 0x28
			std::uint8_t numProjectiles;								  // 0x2C
		};

		static_assert(sizeof(RangedData) == 0x30);

		class __declspec(novtable) InstanceData : public TBO_InstanceData // 0x00
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::TESObjectWEAP__InstanceData;
			inline static constexpr const auto& VTABLE = VTABLE::TESObjectWEAP__InstanceData;

			~InstanceData() override; // 0x00

			// members
			BGSSoundDescriptorForm* attackSound;										// 0x010
			BGSSoundDescriptorForm* attackSound2D;										// 0x018
			BGSSoundDescriptorForm* attackLoop;											// 0x020
			BGSSoundDescriptorForm* attackFailSound;									// 0x028
			BGSSoundDescriptorForm* idleSound;											// 0x030
			BGSSoundDescriptorForm* equipSound;											// 0x038
			BGSSoundDescriptorForm* unEquipSound;										// 0x040
			BGSSoundDescriptorForm* fastEquipSound;										// 0x048
			BGSBlockBashData* blockBashData;											// 0x050
			BGSImpactDataSet* impactDataSet;											// 0x058
			TESLevItem* npcAddAmmoList;													// 0x060
			TESAmmo* ammo;																// 0x068
			BGSEquipSlot* equipSlot;													// 0x070
			SpellItem* effect;															// 0x078
			BGSKeywordForm* keywords;													// 0x080
			BGSAimModel* aimModel;														// 0x088
			BGSZoomData* zoomData;														// 0x090
			RangedData* rangedData;														// 0x098
			BSTArray<EnchantmentItem*>* enchantments;									// 0x0A0
			BSTArray<BGSMaterialSwap*>* materialSwaps;									// 0x0A8
			BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* damageTypes; // 0x0B0
			BSTArray<BSTPair<TESForm*, BGSTypedFormValuePair::SharedVal>>* actorValues; // 0x0B8
			REX::Float32 attackSeconds;													// 0x0C0
			REX::Float32 reloadSpeed;													// 0x0C4
			REX::Float32 speed;															// 0x0C8
			REX::Float32 reach;															// 0x0CC
			REX::Float32 minRange;														// 0x0D0
			REX::Float32 maxRange;														// 0x0D4
			REX::Float32 attackDelaySec;												// 0x0D8
			REX::Float32 damageToWeaponMult;											// 0x0DC
			REX::Float32 outOfRangeDamageMult;											// 0x0E0
			REX::Float32 secondaryDamage;												// 0x0E4
			REX::Float32 criticalChargeBonus;											// 0x0E8
			REX::Float32 weight;														// 0x0EC
			REX::Float32 soundLevelMult;												// 0x0F0
			REX::Float32 attackActionPointCost;											// 0x0F4
			REX::Float32 fullPowerSeconds;												// 0x0F8
			REX::Float32 minPowerPerShot;												// 0x0FC
			REX::Float32 colorRemappingIndex;											// 0x100
			REX::Float32 criticalDamageMult;											// 0x104
			REX::Enum<STAGGER_MAGNITUDE, std::int32_t> staggerValue;					// 0x108
			std::uint32_t value;														// 0x10C
			REX::EnumSet<WEAPON_FLAGS, std::uint32_t> flags;							// 0x110
			REX::Enum<SOUND_LEVEL, std::int32_t> soundLevel;							// 0x114
			REX::Enum<WEAPONHITBEHAVIOR, std::int32_t> hitBehavior;						// 0x118
			ActorValueInfo* skill;														// 0x120
			ActorValueInfo* resistance;													// 0x128
			std::uint16_t ammoCapacity;													// 0x130
			std::uint16_t attackDamage;													// 0x132
			std::uint16_t rank;															// 0x134
			std::uint8_t accuracyBonus;													// 0x136
			REX::Enum<WEAPON_TYPE, std::int8_t> type;									// 0x137
		};

		static_assert(sizeof(InstanceData) == 0x138);

		class __declspec(novtable) Data : public InstanceData // 0x00
		{
		public:
			inline static constexpr const auto& RTTI = RTTI::TESObjectWEAP__Data;
			inline static constexpr const auto& VTABLE = VTABLE::TESObjectWEAP__Data;

			~Data() override; // 0x00
		};

		static_assert(sizeof(Data) == 0x138);

		~TESObjectWEAP() override; // 0x00

		[[nodiscard]]
		auto GetMeleeAttackSpeed() const -> MELEE_ATTACK_SPEED
		{
			using FuncType = decltype(&TESObjectWEAP::GetMeleeAttackSpeed);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectWEAP::GetMeleeAttackSpeed);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		static auto GetMeleeAttackSpeedLabel(MELEE_ATTACK_SPEED a_speed) -> const char*
		{
			using FuncType = decltype(&TESObjectWEAP::GetMeleeAttackSpeedLabel);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectWEAP::GetMeleeAttackSpeedLabel);
			return std::invoke(FUNC, a_speed);
		}

		[[nodiscard]]
		auto GetShotsPerSecond(InstanceData* a_instanceData) const -> REX::Float32
		{
			using FuncType = decltype(&TESObjectWEAP::GetShotsPerSecond);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectWEAP::GetShotsPerSecond);
			return std::invoke(FUNC, this, a_instanceData);
		}

		[[nodiscard]]
		auto IsMeleeWeapon() const noexcept -> bool
		{
			return weaponData.type.any(
				WEAPON_TYPE::OneHandSword,
				WEAPON_TYPE::OneHandDagger,
				WEAPON_TYPE::OneHandAxe,
				WEAPON_TYPE::OneHandMace,
				WEAPON_TYPE::TwoHandSword,
				WEAPON_TYPE::TwoHandAxe);
		}

		[[nodiscard]]
		auto IsGunWeapon() const noexcept -> bool
		{
			return weaponData.type.any(WEAPON_TYPE::Gun);
		}

		[[nodiscard]]
		auto IsThrownWeapon() const -> bool
		{
			return weaponData.type.any(WEAPON_TYPE::Grenade, WEAPON_TYPE::Mine);
		}

		[[nodiscard]]
		auto IsOneHandedWeapon() const noexcept -> bool
		{
			return weaponData.type.any(
				WEAPON_TYPE::OneHandSword,
				WEAPON_TYPE::OneHandDagger,
				WEAPON_TYPE::OneHandAxe,
				WEAPON_TYPE::OneHandMace);
		}

		[[nodiscard]]
		auto IsTwoHandedWeapon() const noexcept -> bool
		{
			return weaponData.type.any(WEAPON_TYPE::TwoHandSword, WEAPON_TYPE::TwoHandAxe);
		}

		[[nodiscard]]
		auto IsRangedWeapon() const noexcept -> bool
		{
			return weaponData.type.any(
				WEAPON_TYPE::Bow,
				WEAPON_TYPE::Staff,
				WEAPON_TYPE::Gun,
				WEAPON_TYPE::Grenade,
				WEAPON_TYPE::Mine);
		}

		[[nodiscard]]
		auto IsBoundWeapon() const noexcept -> bool
		{
			return weaponData.flags.any(WEAPON_FLAGS::BoundWeapon);
		}

		[[nodiscard]]
		auto IsEmbeddedWeapon() const noexcept -> bool
		{
			return weaponData.flags.any(WEAPON_FLAGS::EmbeddedWeapon);
		}

		// members
		TESObjectWEAP::Data weaponData;				// 0x198
		BGSModelMaterialSwap* firstPersonModel;		// 0x2D0
		TESObjectWEAP* weaponTemplate;				// 0x2D8
		BGSMod::Attachment::Mod* embeddedWeaponMod; // 0x2E0
		BGSAttachParentArray attachParents;			// 0x2E8
	};

	static_assert(sizeof(TESObjectWEAP) == 0x300);
}
