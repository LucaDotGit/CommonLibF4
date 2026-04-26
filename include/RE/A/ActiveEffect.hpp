#pragma once

#include "RE/A/ActiveEffectReferenceEffectController.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/F/FormType.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::MagicSystem
{
	enum class CastingSource : std::int32_t;
}

namespace RE
{
	class EffectItem;
	class MagicTarget;
	class NiNode;
	class ReferenceEffect;

	class __declspec(novtable) ActiveEffect
		: public BSIntrusiveRefCounted // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ActiveEffect };
		inline static constexpr auto VTABLE{ VTABLE::ActiveEffect };
		inline static constexpr auto FORM_TYPE{ FormType::kActiveEffect };

		inline static constexpr auto INVALID_UNIQUE_ID = std::numeric_limits<ContainerID>::max();

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kNoHitShader = 1 << 1,
			kNoHitEffectArt = 1 << 2,
			kNoInitialFlare = 1 << 4,
			kApplyingHitEffects = 1 << 5,
			kApplyingSounds = 1 << 6,
			kHasConditions = 1 << 7,
			kRecover = 1 << 9,
			kDualCasted = 1 << 12,
			kInactive = 1 << 15,
			kAppliedEffects = 1 << 16,
			kRemovedEffects = 1 << 17,
			kDispelled = 1 << 18,
			kWornOff = 1ui32 << 31
		};

		enum class ConditionStatus : std::int32_t
		{
			kNotAvailable = -1,
			kFalse = 0,
			kTrue = 1
		};

		virtual ~ActiveEffect(); // 00

		[[nodiscard]] std::uint16_t GetUniqueID() const noexcept { return uniqueID; }

		[[nodiscard]] FormType GetFormType() const noexcept;

		[[nodiscard]] bool CheckDisplacementSpellOnTarget();
		[[nodiscard]] NiPointer<Actor> GetTargetActor() const;

		// members
		ActiveEffectReferenceEffectController hitEffectController;		   // 0C
		BSSoundHandle persistentSound;									   // 30
		ActorHandle caster;												   // 38
		NiPointer<NiNode> sourceNode;									   // 40
		MagicItem* spell;												   // 48
		EffectItem* effect;												   // 50
		MagicTarget* target;											   // 58
		TESBoundObject* source;											   // 60
		BSSimpleList<ReferenceEffect*>* hitEffects;						   // 68
		MagicItem* displacementSpell;									   // 70
		REX::Float32 elapsedSeconds;									   // 74
		REX::Float32 duration;											   // 78
		REX::Float32 magnitude;											   // 7C
		REX::EnumSet<Flags, std::uint32_t> flags;						   // 80
		REX::Enum<ConditionStatus, std::int32_t> conditionStatus;		   // 84
		ContainerID uniqueID;											   // 8C
		REX::Enum<MagicSystem::CastingSource, std::int32_t> castingSource; // 90
	};
	static_assert(sizeof(ActiveEffect) == 0x98);
}
