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

	class __declspec(novtable) MagicItem :
		public TESBoundObject, // 0x00
		public TESFullName,	   // 0x68
		public BGSKeywordForm  // 0x70
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::MagicItem;
		inline static constexpr const auto& VTABLE = VTABLE::MagicItem;
		inline static constexpr auto FORM_TYPE = FormType::None;

		class SkillUsageData
		{
		public:
			// members
			EffectItem* effect;		// 0x00
			ActorValueInfo* skill;	// 0x08
			REX::Float32 magnitude; // 0x10
			bool custom;			// 0x14
		};

		static_assert(sizeof(SkillUsageData) == 0x18);

		class Data
		{
		public:
			enum class Flags : std::uint32_t
			{
				None = 0,

				// 0xAlchemyItem, EnchantmentItem, SpellItem
				ManualCostCalc = 1 << 0,

				// 0xAlchemyItem
				Food = 1 << 1,
				Medicine = 1 << 16,
				Poison = 1 << 17,

				// 0xEnchantmentItem
				FoodItem = 1 << 1,
				ExtendDuration = 1 << 3,

				// SpellItem
				PCStartSpell = 1 << 17,
				InstantCast = 1 << 18,
				AreaEffectIgnoresLOS = 1 << 19,
				IgnoresResist = 1 << 20,
				NoAbsorbReflect = 1 << 21,
				NoDualCastMods = 1 << 23
			};

			// members
			std::int32_t costOverride;				  // 0x00
			REX::EnumSet<Flags, std::uint32_t> flags; // 0x04
		};

		static_assert(sizeof(Data) == 0x08);

		~MagicItem() override; // 0x00

		// add
		virtual auto GetSpellType() const -> MagicSystem::SpellType = 0;		// 0x67
		virtual void SetCastingType(MagicSystem::CastingType a_castingType);	// 0x68 - { return; }
		virtual auto GetCastingType() const -> MagicSystem::CastingType = 0;	// 0x69
		virtual void SetDelivery(MagicSystem::Delivery a_delivery);				// 0x6A - { return; }
		virtual auto GetDelivery() const -> MagicSystem::Delivery = 0;			// 0x6B
		virtual auto IsValidDelivery(MagicSystem::Delivery a_delivery) -> bool; // 0x6C - { return true; }
		virtual auto GetFixedCastDuration() const -> REX::Float32; // 0x6D - { return static_cast<REX::Float32>(0.0); }
		virtual auto GetRange() const -> REX::Float32;			   // 0x6E - { return static_cast<REX::Float32>(0.0); }
		virtual auto IgnoreResistance() const -> bool;			   // 0x6F - { return false; }
		virtual auto IgnoreLOS() const -> bool;					   // 0x70 - { return false; }
		virtual auto IsFood() const -> bool;					   // 0x71 - { return false; }
		virtual auto GetNoAbsorb() const -> bool;				   // 0x72 - { return false; }
		virtual auto GetNoDualCastModifications() const -> bool;   // 0x73 - { return false; }
		virtual auto GetSkillUsageData(SkillUsageData& a_data) const -> bool; // 0x74 - { return false; }
		virtual auto IsPoison() const -> bool;								  // 0x75
		virtual auto IsMedicine() const -> bool;							  // 0x76 - { return false; }
		virtual void AdjustCost(REX::Float32& a_cost, Actor* a_actor) const;  // 0x77 - { return; }
		virtual auto GetChargeTime() const -> REX::Float32;			// 0x78 - { return static_cast<REX::Float32>(0.0); }
		virtual auto GetMaxEffectCount() const -> std::uint32_t;	// 0x79 - { return 0; }
		virtual auto GetAssociatedSkill() const -> ActorValueInfo*; // 0x7A - { return nullptr; }
		virtual auto IsTwoHanded() const -> bool;					// 0x7B - { return false; }
		virtual auto GetChunkID() -> CHUNK_ID = 0;					// 0x7C
		virtual void CopyMagicItemData(MagicItem* a_copy) = 0;		// 0x7D
		virtual void LoadMagicItemChunk(TESFile* a_file, CHUNK_ID a_chunkID); // 0x7E - { return; }
		virtual void LoadChunkDataPostProcess(TESFile* a_file);				  // 0x7F - { return; }
		virtual auto GetData() -> Data* = 0;								  // 0x81
		virtual auto GetData() const -> const Data* = 0;					  // 0x80
		virtual auto GetDataSize() const -> std::size_t = 0;				  // 0x82
		virtual void InitFromChunk(TESFile* a_file) = 0;					  // 0x83

		void SetEffects(std::span<std::unique_ptr<EffectItem>> a_effects);
		void ClearEffects();

		// members
		BSTArray<EffectItem*> listOfEffects;		  // 0x98
		std::int32_t hostileCount;					  // 0xB0
		EffectSetting* avEffectSetting;				  // 0xB8
		std::uint32_t preloadCount;					  // 0xC0
		BSTGamebryoPointer<QueuedFile> preloadedItem; // 0xC8
	};

	static_assert(sizeof(MagicItem) == 0xD0);
}
