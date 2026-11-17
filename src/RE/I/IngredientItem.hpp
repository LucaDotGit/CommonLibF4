#pragma once

#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSEquipType.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSPickupPutdownSounds.hpp"
#include "RE/M/MagicItem.hpp"
#include "RE/T/TESIcon.hpp"
#include "RE/T/TESValueForm.hpp"
#include "RE/T/TESWeightForm.hpp"

namespace RE
{
	class __declspec(novtable) IngredientItem :
		public MagicItem,				  // 0x000
		public BGSModelMaterialSwap,	  // 0x0D0
		public TESIcon,					  // 0x110
		public TESWeightForm,			  // 0x120
		public BGSEquipType,			  // 0x130
		public BGSDestructibleObjectForm, // 0x140
		public BGSPickupPutdownSounds,	  // 0x150
		public TESValueForm				  // 0x168
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IngredientItem;
		inline static constexpr const auto& VTABLE = VTABLE::IngredientItem;
		inline static constexpr auto FORM_TYPE = FormType::Ingredient;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Use = static_cast<std::uint32_t>(1) << 31
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None = 0,
			CostOverride = 1 << 0,
			FoodItem = 1 << 1,
			ExtendDuration = 1 << 3,
			ReferencesPersist = 1 << 8
		};

		class GameData
		{
		public:
			// members
			std::uint16_t knownEffectFlags; // 0x00
			std::uint16_t playerUses;		// 0x02
		};

		static_assert(sizeof(GameData) == 0x04);

		~IngredientItem() override; // 0x00

		// members
		MagicItem::Data data; // 0x178
		GameData gameData;	  // 0x180
	};

	static_assert(sizeof(IngredientItem) == 0x188);
}
