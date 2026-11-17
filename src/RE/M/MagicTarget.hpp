#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE::MagicSystem
{
	enum class CastingSource : std::int32_t;
}

namespace RE
{
	class ActiveEffectList;
	class EffectItem;

	class __declspec(novtable) MagicTarget
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::MagicTarget;
		inline static constexpr const auto& VTABLE = VTABLE::MagicTarget;

		enum class Flags : std::uint8_t
		{
			None = 0,
			Updating = 1 << 0,
			Invisible = 1 << 1
		};

		class __declspec(novtable) IPostCreationModification
		{
		public:
			virtual ~IPostCreationModification() = default; // 0x00

			// add
			virtual void ModifyActiveEffect(ActiveEffect* a_effect); // 0x01

			GAME_HEAP_REDEFINE_NEW(IPostCreationModification);
		};

		static_assert(sizeof(IPostCreationModification) == 0x08);

		class ResultCollector
		{
		public:
			GAME_HEAP_REDEFINE_NEW(ResultCollector);

			// members
			TESObjectREFR* target;	   // 0x00
			TESObjectREFR* caster;	   // 0x08
			MagicItem* spell;		   // 0x10
			std::uint16_t immunities;  // 0x18
			std::uint16_t nonTrivials; // 0x1A
		};

		static_assert(sizeof(ResultCollector) == 0x20);

		class AddTargetData
		{
		public:
			GAME_HEAP_REDEFINE_NEW(AddTargetData);

			// members
			TESObjectREFR* caster;					  // 0x00
			MagicItem* spell;						  // 0x08
			EffectItem* effect;						  // 0x10
			TESBoundObject* source;					  // 0x18
			IPostCreationModification* callback;	  // 0x20
			ResultCollector* resultCollector;		  // 0x28
			NiPoint3 explosionLocation;				  // 0x30
			REX::Float32 magnitude;					  // 0x3C
			MagicSystem::CastingSource castingSource; // 0x40
			bool areaTarget;						  // 0x44
			bool dualCast;							  // 0x45
		};

		static_assert(sizeof(AddTargetData) == 0x48);

		class SpellDispelData
		{
		public:
			GAME_HEAP_REDEFINE_NEW(SpellDispelData);

			// members
			MagicItem* spell;							// 0x00
			BSPointerHandle<Actor> caster;				// 0x08
			BSTSmartPointer<ActiveEffect> activeEffect; // 0x10
			SpellDispelData* next;						// 0x18
		};

		static_assert(sizeof(SpellDispelData) == 0x20);

		virtual ~MagicTarget(); // 0x00

		// add
		virtual auto AddTarget(AddTargetData& a_data) -> bool;				 // 0x01
		virtual auto GetTargetStatsObject() -> TESObjectREFR*;				 // 0x02 - { return nullptr; }
		virtual auto MagicTargetIsActor() -> bool;							 // 0x03 - { return false; }
		virtual auto IsInvulnerable() const -> bool;						 // 0x04 - { return false; }
		virtual void InvalidateCommandedActorEffect(ActiveEffect* a_effect); // 0x05 - { return; }
		virtual auto CanAddActiveEffect() const -> bool = 0;				 // 0x06
		virtual auto GetActiveEffectList() -> ActiveEffectList* = 0;		 // 0x07
		virtual auto CheckResistance(MagicItem* a_spell, EffectItem* a_effect, TESBoundObject* a_source) const
			-> REX::Float32;								// 0x08 - { return static_cast<REX::Float32>(1.0); }
		virtual void EffectAdded(ActiveEffect* a_effect);	// 0x09 - { return; }
		virtual void EffectRemoved(ActiveEffect* a_effect); // 0x0A - { return; }
		virtual void EffectActiveStatusChanged(ActiveEffect* a_effect); // 0x0B - { return; }
		virtual auto CheckAbsorb(
			Actor* a_caster,
			MagicItem* a_spell,
			const EffectItem* a_effectItem) -> bool; // 0x0C - { return false; }

		[[nodiscard]]
		auto IsTakingHealthDamageFromActiveEffect() const -> bool;
		[[nodiscard]]
		auto IsTakingRadDamageFromActiveEffect() const -> bool;

		[[nodiscard]]
		auto GetActiveEffectByID(std::uint16_t a_id) const -> BSTSmartPointer<ActiveEffect>;

		// members
		SpellDispelData* postUpdateDispelList;	 // 0x08
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x10
	};

	static_assert(sizeof(MagicTarget) == 0x18);
}
