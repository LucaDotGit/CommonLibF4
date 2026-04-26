#pragma once

#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BGSMenuDisplayObject.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE::EffectArchetypes
{
	enum class ArchetypeID : std::int32_t;
}

namespace RE::MagicSystem
{
	enum class CastingType : std::int32_t;
	enum class Delivery : std::int32_t;
	enum class SoundID : std::int32_t;
}

namespace RE
{
	enum class SOUND_LEVEL : std::int32_t;

	class __declspec(novtable) EffectSetting
		: public TESForm,			   // 000
		  public TESFullName,		   // 020
		  public BGSMenuDisplayObject, // 030
		  public BGSKeywordForm		   // 040
	{
	public:
		inline static constexpr auto RTTI{ RTTI::EffectSetting };
		inline static constexpr auto VTABLE{ VTABLE::EffectSetting };
		inline static constexpr auto FORM_TYPE{ FormType::kMagicEffect };

		using FilterValidationFunctionType = bool(EffectSetting*, void*);

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class EffectSettingData
		{
		public:
			enum class Flags : std::uint32_t
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
			REX::Float32 baseCost;											  // 004
			TESForm* associatedForm;										  // 008
			ActorValueInfo* associatedSkill;								  // 010
			ActorValueInfo* resistVariable;									  // 018
			std::int16_t numCounterEffects;									  // 020
			TESObjectLIGH* light;											  // 028
			REX::Float32 taperWeight;										  // 030
			TESEffectShader* effectShader;									  // 038
			TESEffectShader* enchantEffect;									  // 040
			std::int32_t minimumSkill;										  // 048
			std::int32_t spellmakingArea;									  // 04C
			REX::Float32 spellmakingChargeTime;								  // 050
			REX::Float32 taperCurve;										  // 054
			REX::Float32 taperDuration;										  // 058
			REX::Float32 secondaryAVWeight;									  // 05C
			REX::Enum<EffectArchetypes::ArchetypeID, std::int32_t> archetype; // 060
			ActorValueInfo* primaryAV;										  // 068
			BGSProjectile* projectileBase;									  // 070
			BGSExplosion* explosion;										  // 078
			REX::Enum<MagicSystem::CastingType, std::int32_t> castingType;	  // 080
			REX::Enum<MagicSystem::Delivery, std::int32_t> delivery;		  // 084
			ActorValueInfo* secondaryAV;									  // 088
			BGSArtObject* castingArt;										  // 090
			BGSArtObject* hitEffectArt;										  // 098
			BGSImpactDataSet* impactDataSet;								  // 0A0
			REX::Float32 skillUsageMult;									  // 0A8
			BGSDualCastData* dualCastData;									  // 0B0
			REX::Float32 dualCastScale;										  // 0B8
			BGSArtObject* enchantEffectArt;									  // 0C0
			BGSReferenceEffect* hitVisuals;									  // 0C8
			BGSReferenceEffect* enchantVisuals;								  // 0D0
			SpellItem* equipAbility;										  // 0D8
			TESImageSpaceModifier* imageSpaceMod;							  // 0E0
			BGSPerk* perk;													  // 0E8
			REX::Enum<SOUND_LEVEL, std::int32_t> castingSoundLevel;			  // 0F0
			REX::Float32 aiScore;											  // 0F4
			REX::Float32 aiDelayTime;										  // 0F8
		};
		static_assert(sizeof(EffectSettingData) == 0x100);

		class SoundPair
		{
		public:
			// members
			REX::Enum<MagicSystem::SoundID, std::int32_t> id; // 00
			BGSSoundDescriptorForm* sound;					  // 08
		};
		static_assert(sizeof(SoundPair) == 0x10);

		// members
		FilterValidationFunctionType* filterValidationFunction; // 060
		void* filterValidationItem;								// 068
		EffectSettingData data;									// 070
		BSSimpleList<EffectSetting*> counterEffects;			// 170
		BSTArray<EffectSetting::SoundPair> effectSounds;		// 180
		BGSLocalizedString magicItemDescription;				// 198
		std::uint32_t effectLoadedCount;						// 1A0
		std::uint32_t associatedItemLoadedCount;				// 1A4
		TESCondition conditions;								// 1A8
	};
	static_assert(sizeof(EffectSetting) == 0x1B0);
}
