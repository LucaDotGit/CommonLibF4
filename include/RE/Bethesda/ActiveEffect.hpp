#pragma once

#include "RE/Bethesda/BSSoundHandle.hpp"
#include "RE/Bethesda/ReferenceEffectController.hpp"
#include "RE/Bethesda/TESForms.hpp"

namespace RE
{
	class ActiveEffect;
	class EffectItem;
	class MagicItem;
	class MagicTarget;
	class ReferenceEffect;
	class TESForm;
	class TESObjectREFR;

	namespace MagicSystem
	{
		enum class CastingSource;
	}

	class __declspec(novtable) ActiveEffect
		: public BSIntrusiveRefCounted
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ActiveEffect };
		inline static constexpr auto VTABLE{ VTABLE::ActiveEffect };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kActiveEffect };

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kNoHitShader = 1u << 1,
			kNoHitEffectArt = 1u << 2,
			kNoInitialFlare = 1u << 4,
			kApplyingHitEffects = 1u << 5,
			kApplyingSounds = 1u << 6,
			kHasConditions = 1u << 7,
			kRecover = 1u << 9,
			kDualCasted = 1u << 12,
			kInactive = 1u << 15,
			kAppliedEffects = 1u << 16,
			kRemovedEffects = 1u << 17,
			kDispelled = 1u << 18,
			kWornOff = 1u << 31
		};

		enum class ConditionStatus : std::uint32_t
		{
			kNotAvailable = static_cast<std::underlying_type_t<ConditionStatus>>(-1),
			kFalse = 0,
			kTrue = 1
		};

		virtual ~ActiveEffect();

		bool CheckDisplacementSpellOnTarget()
		{
			using func_t = decltype(&ActiveEffect::CheckDisplacementSpellOnTarget);
			static REL::Relocation<func_t> func{ REL::ID(1415178) };
			return func(this);
		}

		// members
		ActiveEffectReferenceEffectController hitEffectController;			// 0C
		BSSoundHandle persistentSound;										// 30
		ActorHandle caster;													// 38
		NiPointer<NiNode> sourceNode;										// 40
		MagicItem* spell;													// 48
		EffectItem* effect;													// 50
		MagicTarget* target;												// 58
		TESBoundObject* source;												// 60
		BSSimpleList<ReferenceEffect*>* hitEffects;							// 68
		MagicItem* displacementSpell;										// 70
		float elapsedSeconds;												// 78
		float duration;														// 7C
		float magnitude;													// 80
		REX::EnumSet<Flags, std::uint32_t> flags;							// 84
		REX::Enum<ConditionStatus, std::int32_t> conditionStatus;			// 88
		std::uint16_t uniqueID;												// 8C
		std::uint16_t pad8e;												// 8E
		REX::Enum<MagicSystem::CastingSource, std::uint32_t> castingSource; // 90
		std::uint32_t pad94;												// 94
	};
	static_assert(sizeof(ActiveEffect) == 0x98);
}
