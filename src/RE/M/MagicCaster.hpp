#pragma once

#include "RE/A/ActorValue.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::MagicSystem
{
	enum class CannotCastReason : std::int32_t;
	enum class CastingSource : std::int32_t;
	enum class SoundID : std::int32_t;
}

namespace RE
{
	class BGSLoadGameBuffer;
	class BGSSaveGameBuffer;
	class BSSoundHandle;
	class NiNode;

	class __declspec(novtable) MagicCaster
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::MagicCaster;
		inline static constexpr const auto& VTABLE = VTABLE::MagicCaster;

		using State = ActorValue::AVType;

		virtual ~MagicCaster(); // 0x00

		// add
		virtual void Update(REX::Float32 a_deltaTime); // 0x01
		virtual void CastSpellImmediate(
			MagicItem* a_spell,
			bool a_loadCast,
			TESObjectREFR* a_desiredTarget,
			REX::Float32 a_effectivenessMult,
			bool a_adjustOnlyHostileEffectiveness,
			REX::Float32 a_magnitudeOverride,
			Actor* a_blameActor);																// 0x02
		virtual void FindTouchTarget();															// 0x03
		virtual void RequestCastImpl();															// 0x04
		virtual auto StartChargeImpl() -> bool;													// 0x05
		virtual void StartReadyImpl();															// 0x06
		virtual void StartCastImpl();															// 0x07
		virtual void FinishCastImpl();															// 0x08 - { return; }
		virtual void InterruptCastImpl(bool a_depleteEnergy);									// 0x09 - { return; }
		virtual void SpellCast(bool a_doCast, std::uint32_t a_targetCount, MagicItem* a_spell); // 0x0A - { return; }
		virtual auto CheckCast(
			MagicItem* a_spell,
			bool a_dualCast,
			REX::Float32* a_effectStrength,
			MagicSystem::CannotCastReason* a_reason,
			bool a_useBaseValueForCost) -> bool;											// 0x0B
		virtual auto GetCasterStatsObject() const -> TESObjectREFR*;						// 0x0C - { return 0; }
		virtual auto GetCasterAsActor() const -> Actor*;									// 0x0D - { return 0; }
		virtual auto GetCasterObjectReference(Actor*& a_outCaster) const -> TESObjectREFR*; // 0x0E
		virtual auto GetMagicNode() -> NiNode*;												// 0x0F - { return 0; }
		virtual void ClearMagicNode();														// 0x10 - { return; }
		virtual void SetCurrentSpellImpl(MagicItem* a_spell);								// 0x11 - { return; }
		virtual void SelectSpellImpl();														// 0x12 - { return; }
		virtual void DeselectSpellImpl();													// 0x13 - { return; }
		virtual void SetSkipCheckCast();													// 0x14 - { return; }
		virtual void SetCastingTimerForCharge();											// 0x15
		virtual auto GetCastingSource() const -> MagicSystem::CastingSource;				// 0x16 - { return 0; }
		virtual auto GetIsDualCasting() const -> bool;										// 0x17 - { return 0; }
		virtual void SetDualCasting(bool a_set);											// 0x18 - { return; }
		virtual void SaveGame(BGSSaveGameBuffer& a_buffer);									// 0x19
		virtual void LoadGame(BGSLoadGameBuffer& a_buffer);									// 0x20
		virtual void FinishLoadGame(BGSLoadGameBuffer& a_buffer);							// 0x21
		virtual void PrepareSound(MagicSystem::SoundID a_sound, MagicItem* a_spell);		// 0x22
		virtual void AdjustActiveEffect(
			ActiveEffect* a_activeEffect,
			REX::Float32 a_strength,
			bool a_adjustOnlyHostileEffectiveness); // 0x23

		auto FindTargets(
			REX::Float32 a_effectivenessMult,
			std::uint32_t& a_outTargetCount,
			TESBoundObject* a_source,
			bool a_loadCast,
			bool a_adjustOnlyHostileEffectiveness) -> bool
		{
			using FuncType = decltype(&MagicCaster::FindTargets);
			static const auto FUNC = REL::Relocation<FuncType>(ID::MagicCaster::FindTargets);
			return std::invoke(
				FUNC,
				this,
				a_effectivenessMult,
				a_outTargetCount,
				a_source,
				a_loadCast,
				a_adjustOnlyHostileEffectiveness);
		}

		// members
		BSTArray<BSSoundHandle> sounds;			  // 0x08
		ObjectRefHandle desiredTarget;			  // 0x20
		MagicItem* currentSpell;				  // 0x28
		REX::EnumSet<State, std::uint32_t> state; // 0x30
		REX::Float32 castingTimer;				  // 0x34
		REX::Float32 currentSpellCost;			  // 0x38
		REX::Float32 magnitudeOverride;			  // 0x3C
		REX::Float32 nextTargetUpdate;			  // 0x40
		REX::Float32 projectileTimer;			  // 0x44
	};

	static_assert(sizeof(MagicCaster) == 0x48);
}
