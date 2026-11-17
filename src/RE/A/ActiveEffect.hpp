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

	class __declspec(novtable) ActiveEffect : public BSIntrusiveRefCounted // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ActiveEffect;
		inline static constexpr const auto& VTABLE = VTABLE::ActiveEffect;
		inline static constexpr auto FORM_TYPE = FormType::ActiveEffect;

		inline static constexpr auto INVALID_UNIQUE_ID = std::numeric_limits<ContainerID>::max();

		enum class Flags : std::uint32_t
		{
			None = 0,
			NoHitShader = 1 << 1,
			NoHitEffectArt = 1 << 2,
			NoInitialFlare = 1 << 4,
			ApplyingHitEffects = 1 << 5,
			ApplyingSounds = 1 << 6,
			HasConditions = 1 << 7,
			Recover = 1 << 9,
			DualCasted = 1 << 12,
			Inactive = 1 << 15,
			AppliedEffects = 1 << 16,
			RemovedEffects = 1 << 17,
			Dispelled = 1 << 18,
			WornOff = static_cast<std::uint32_t>(1) << 31
		};

		enum class ConditionStatus : std::int32_t
		{
			NotAvailable = -1,
			False = 0,
			True = 1
		};

		virtual ~ActiveEffect(); // 0x00

		[[nodiscard]]
		auto GetUniqueID() const noexcept -> std::uint16_t
		{
			return uniqueID;
		}

		[[nodiscard]]
		auto GetFormType() const noexcept -> FormType;

		[[nodiscard]]
		auto CheckDisplacementSpellOnTarget() -> bool;
		[[nodiscard]]
		auto GetTargetActor() const -> NiPointer<Actor>;

		// members
		ActiveEffectReferenceEffectController hitEffectController;		   // 0x10
		BSSoundHandle persistentSound;									   // 0x30
		ActorHandle caster;												   // 0x38
		NiPointer<NiNode> sourceNode;									   // 0x40
		MagicItem* spell;												   // 0x48
		EffectItem* effect;												   // 0x50
		MagicTarget* target;											   // 0x58
		TESBoundObject* source;											   // 0x60
		BSSimpleList<ReferenceEffect*>* hitEffects;						   // 0x68
		MagicItem* displacementSpell;									   // 0x70
		REX::Float32 elapsedSeconds;									   // 0x78
		REX::Float32 duration;											   // 0x7C
		REX::Float32 magnitude;											   // 0x80
		REX::EnumSet<Flags, std::uint32_t> flags;						   // 0x84
		REX::Enum<ConditionStatus, std::int32_t> conditionStatus;		   // 0x88
		ContainerID uniqueID;											   // 0x8C
		REX::Enum<MagicSystem::CastingSource, std::int32_t> castingSource; // 0x90
	};

	static_assert(sizeof(ActiveEffect) == 0x98);
}
