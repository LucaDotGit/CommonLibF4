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

	class __declspec(novtable) EffectSetting :
		public TESForm,				 // 0x000
		public TESFullName,			 // 0x020
		public BGSMenuDisplayObject, // 0x030
		public BGSKeywordForm		 // 0x040
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::EffectSetting;
		inline static constexpr const auto& VTABLE = VTABLE::EffectSetting;
		inline static constexpr auto FORM_TYPE = FormType::MagicEffect;

		using FilterValidationFunctionType = bool(EffectSetting*, void*);

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class EffectSettingData
		{
		public:
			enum class Flags : std::uint32_t
			{
				None = 0,
				Hostile = 1 << 0,
				Recover = 1 << 1,
				Detrimental = 1 << 2,
				SnapToNavMesh = 1 << 3,
				NoHitEvent = 1 << 4,
				DispelWithKeywords = 1 << 8,
				NoDuration = 1 << 9,
				NoMagnitude = 1 << 10,
				NoArea = 1 << 11,
				FXPersist = 1 << 12,
				GoryVisuals = 1 << 14,
				HideInUI = 1 << 15,
				NoRecast = 1 << 17,
				PowerAffectsMagnitude = 1 << 21,
				PowerAffectsDuration = 1 << 22,
				Painless = 1 << 26,
				NoHitEffect = 1 << 27,
				NoDeathDispel = 1 << 28
			};

			// members
			REX::EnumSet<Flags, std::uint32_t> flags;						  // 0x000
			REX::Float32 baseCost;											  // 0x004
			TESForm* associatedForm;										  // 0x008
			ActorValueInfo* associatedSkill;								  // 0x010
			ActorValueInfo* resistVariable;									  // 0x018
			std::int16_t numCounterEffects;									  // 0x020
			TESObjectLIGH* light;											  // 0x028
			REX::Float32 taperWeight;										  // 0x030
			TESEffectShader* effectShader;									  // 0x038
			TESEffectShader* enchantEffect;									  // 0x040
			std::int32_t minimumSkill;										  // 0x048
			std::int32_t spellmakingArea;									  // 0x04C
			REX::Float32 spellmakingChargeTime;								  // 0x050
			REX::Float32 taperCurve;										  // 0x054
			REX::Float32 taperDuration;										  // 0x058
			REX::Float32 secondaryAVWeight;									  // 0x05C
			REX::Enum<EffectArchetypes::ArchetypeID, std::int32_t> archetype; // 0x060
			ActorValueInfo* primaryAV;										  // 0x068
			BGSProjectile* projectileBase;									  // 0x070
			BGSExplosion* explosion;										  // 0x078
			REX::Enum<MagicSystem::CastingType, std::int32_t> castingType;	  // 0x080
			REX::Enum<MagicSystem::Delivery, std::int32_t> delivery;		  // 0x084
			ActorValueInfo* secondaryAV;									  // 0x088
			BGSArtObject* castingArt;										  // 0x090
			BGSArtObject* hitEffectArt;										  // 0x098
			BGSImpactDataSet* impactDataSet;								  // 0x0A0
			REX::Float32 skillUsageMult;									  // 0x0A8
			BGSDualCastData* dualCastData;									  // 0x0B0
			REX::Float32 dualCastScale;										  // 0x0B8
			BGSArtObject* enchantEffectArt;									  // 0x0C0
			BGSReferenceEffect* hitVisuals;									  // 0x0C8
			BGSReferenceEffect* enchantVisuals;								  // 0x0D0
			SpellItem* equipAbility;										  // 0x0D8
			TESImageSpaceModifier* imageSpaceMod;							  // 0x0E0
			BGSPerk* perk;													  // 0x0E8
			REX::Enum<SOUND_LEVEL, std::int32_t> castingSoundLevel;			  // 0x0F0
			REX::Float32 aiScore;											  // 0x0F4
			REX::Float32 aiDelayTime;										  // 0x0F8
		};

		static_assert(sizeof(EffectSettingData) == 0x100);

		class SoundPair
		{
		public:
			// members
			REX::Enum<MagicSystem::SoundID, std::int32_t> id; // 0x00
			BGSSoundDescriptorForm* sound;					  // 0x08
		};

		static_assert(sizeof(SoundPair) == 0x10);

		~EffectSetting() override; // 0x00

		// members
		FilterValidationFunctionType* filterValidationFunction; // 0x060
		void* filterValidationItem;								// 0x068
		EffectSettingData data;									// 0x070
		BSSimpleList<EffectSetting*> counterEffects;			// 0x170
		BSTArray<EffectSetting::SoundPair> effectSounds;		// 0x180
		BGSLocalizedString magicItemDescription;				// 0x198
		std::uint32_t effectLoadedCount;						// 0x1A0
		std::uint32_t associatedItemLoadedCount;				// 0x1A4
		TESCondition conditions;								// 0x1A8
	};

	static_assert(sizeof(EffectSetting) == 0x1B0);
}
