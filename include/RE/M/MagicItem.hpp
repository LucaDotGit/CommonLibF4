#pragma once

#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class QueuedFile;
}

namespace RE::MagicSystem
{
	enum class CastingType : std::int32_t;
	enum class Delivery : std::int32_t;
	enum class SpellType : std::int32_t;
}

namespace RE
{
	class EffectItem;

	class __declspec(novtable) MagicItem
		: public TESBoundObject, // 00
		  public TESFullName,	 // 68
		  public BGSKeywordForm	 // 70
	{
	public:
		inline static constexpr auto RTTI{ RTTI::MagicItem };
		inline static constexpr auto VTABLE{ VTABLE::MagicItem };
		inline static constexpr auto FORM_TYPE{ FormType::kNone };

		class SkillUsageData
		{
		public:
			// members
			EffectItem* effect;		// 00
			ActorValueInfo* skill;	// 08
			REX::Float32 magnitude; // 10
			bool custom;			// 14
		};
		static_assert(sizeof(SkillUsageData) == 0x18);

		class Data
		{
		public:
			enum class Flags : std::uint32_t
			{
				kNone = 0,

				// AlchemyItem, EnchantmentItem, SpellItem
				kManualCostCalc = 1 << 0,

				// AlchemyItem
				kFood = 1 << 1,
				kMedicine = 1 << 16,
				kPoison = 1 << 17,

				// EnchantmentItem
				kFoodItem = 1 << 1,
				kExtendDuration = 1 << 3,

				// SpellItem
				kPCStartSpell = 1 << 17,
				kInstantCast = 1 << 18,
				kAreaEffectIgnoresLOS = 1 << 19,
				kIgnoresResist = 1 << 20,
				kNoAbsorbReflect = 1 << 21,
				kNoDualCastMods = 1 << 23
			};

			// members
			std::int32_t costOverride;				  // 00
			REX::EnumSet<Flags, std::uint32_t> flags; // 04
		};
		static_assert(sizeof(Data) == 0x08);

		// add
		virtual MagicSystem::SpellType GetSpellType() const = 0;			  // 67
		virtual void SetCastingType(MagicSystem::CastingType a_castingType);  // 68 - { return; }
		virtual MagicSystem::CastingType GetCastingType() const = 0;		  // 69
		virtual void SetDelivery(MagicSystem::Delivery a_delivery);			  // 6A - { return; }
		virtual MagicSystem::Delivery GetDelivery() const = 0;				  // 6B
		virtual bool IsValidDelivery(MagicSystem::Delivery a_delivery);		  // 6C - { return true; }
		virtual REX::Float32 GetFixedCastDuration() const;					  // 6D - { return 0.0_f32; }
		virtual REX::Float32 GetRange() const;								  // 6E - { return 0.0_f32; }
		virtual bool IgnoreResistance() const;								  // 6F - { return false; }
		virtual bool IgnoreLOS() const;										  // 70 - { return false; }
		virtual bool IsFood() const;										  // 71 - { return false; }
		virtual bool GetNoAbsorb() const;									  // 72 - { return false; }
		virtual bool GetNoDualCastModifications() const;					  // 73 - { return false; }
		virtual bool GetSkillUsageData(SkillUsageData& a_data) const;		  // 74 - { return false; }
		virtual bool IsPoison() const;										  // 75
		virtual bool IsMedicine() const;									  // 76 - { return false; }
		virtual void AdjustCost(REX::Float32& a_cost, Actor* a_actor) const;  // 77 - { return; }
		virtual REX::Float32 GetChargeTime() const;							  // 78 - { return 0.0_f32; }
		virtual std::uint32_t GetMaxEffectCount() const;					  // 79 - { return 0; }
		virtual ActorValueInfo* GetAssociatedSkill() const;					  // 7A - { return nullptr; }
		virtual bool IsTwoHanded() const;									  // 7B - { return false; }
		virtual CHUNK_ID GetChunkID() = 0;									  // 7C
		virtual void CopyMagicItemData(MagicItem* a_copy) = 0;				  // 7D
		virtual void LoadMagicItemChunk(TESFile* a_file, CHUNK_ID a_chunkID); // 7E - { return; }
		virtual void LoadChunkDataPostProcess(TESFile* a_file);				  // 7F - { return; }
		virtual Data* GetData() = 0;										  // 81
		virtual const Data* GetData() const = 0;							  // 80
		virtual std::size_t GetDataSize() const = 0;						  // 82
		virtual void InitFromChunk(TESFile* a_file) = 0;					  // 83

		void SetEffects(std::span<std::unique_ptr<EffectItem>> a_effects);
		void ClearEffects();

		// members
		BSTArray<EffectItem*> listOfEffects;		  // 98
		std::int32_t hostileCount;					  // B0
		EffectSetting* avEffectSetting;				  // B8
		std::uint32_t preloadCount;					  // C0
		BSTGamebryoPointer<QueuedFile> preloadedItem; // C8
	};
	static_assert(sizeof(MagicItem) == 0xD0);
}
