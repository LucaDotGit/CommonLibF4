#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPoint.hpp"

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
		inline static constexpr auto RTTI{ RTTI::MagicTarget };
		inline static constexpr auto VTABLE{ VTABLE::MagicTarget };

		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kUpdating = 1 << 0,
			kInvisible = 1 << 1
		};

		class __declspec(novtable) IPostCreationModification
		{
		public:
			virtual ~IPostCreationModification(); // 00

			// add
			virtual void ModifyActiveEffect(ActiveEffect* a_effect); // 01

			GAME_HEAP_REDEFINE_NEW(IPostCreationModification);
		};
		static_assert(sizeof(IPostCreationModification) == 0x08);

		class ResultCollector
		{
		public:
			GAME_HEAP_REDEFINE_NEW(ResultCollector);

			// members
			TESObjectREFR* target;	   // 00
			TESObjectREFR* caster;	   // 08
			MagicItem* spell;		   // 10
			std::uint16_t immunities;  // 18
			std::uint16_t nonTrivials; // 1A
		};
		static_assert(sizeof(ResultCollector) == 0x20);

		class AddTargetData
		{
		public:
			GAME_HEAP_REDEFINE_NEW(AddTargetData);

			// members
			TESObjectREFR* caster;					  // 00
			MagicItem* spell;						  // 08
			EffectItem* effect;						  // 10
			TESBoundObject* source;					  // 18
			IPostCreationModification* callback;	  // 20
			ResultCollector* resultCollector;		  // 28
			NiPoint3 explosionLocation;				  // 30
			REX::Float32 magnitude;					  // 3C
			MagicSystem::CastingSource castingSource; // 40
			bool areaTarget;						  // 44
			bool dualCast;							  // 45
		};
		static_assert(sizeof(AddTargetData) == 0x48);

		class SpellDispelData
		{
		public:
			GAME_HEAP_REDEFINE_NEW(SpellDispelData);

			// members
			MagicItem* spell;							// 00
			BSPointerHandle<Actor> caster;				// 08
			BSTSmartPointer<ActiveEffect> activeEffect; // 10
			SpellDispelData* next;						// 18
		};
		static_assert(sizeof(SpellDispelData) == 0x20);

		virtual ~MagicTarget(); // 00

		// add
		virtual bool AddTarget(AddTargetData& a_data);																	// 01
		virtual TESObjectREFR* GetTargetStatsObject();																	// 02 - { return nullptr; }
		virtual bool MagicTargetIsActor();																				// 03 - { return false; }
		virtual bool IsInvulnerable() const;																			// 04 - { return false; }
		virtual void InvalidateCommandedActorEffect(ActiveEffect* a_effect);											// 05 - { return; }
		virtual bool CanAddActiveEffect() const = 0;																	// 06
		virtual ActiveEffectList* GetActiveEffectList() = 0;															// 07
		virtual REX::Float32 CheckResistance(MagicItem* a_spell, EffectItem* a_effect, TESBoundObject* a_source) const; // 08 - { return 1.0_f32; }
		virtual void EffectAdded(ActiveEffect* a_effect);																// 09 - { return; }
		virtual void EffectRemoved(ActiveEffect* a_effect);																// 0A - { return; }
		virtual void EffectActiveStatusChanged(ActiveEffect* a_effect);													// 0B - { return; }
		virtual bool CheckAbsorb(Actor* a_caster, MagicItem* a_spell, const EffectItem* a_effectItem);					// 0C - { return false; }

		[[nodiscard]] bool IsTakingHealthDamageFromActiveEffect() const;
		[[nodiscard]] bool IsTakingRadDamageFromActiveEffect() const;

		[[nodiscard]] BSTSmartPointer<ActiveEffect> GetActiveEffectByID(std::uint16_t a_id) const;

		// members
		SpellDispelData* postUpdateDispelList;	 // 08
		REX::EnumSet<Flags, std::uint8_t> flags; // 10
	};
	static_assert(sizeof(MagicTarget) == 0x18);
}
