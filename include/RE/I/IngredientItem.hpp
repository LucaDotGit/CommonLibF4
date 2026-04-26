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
	class __declspec(novtable) IngredientItem
		: public MagicItem,					// 000
		  public BGSModelMaterialSwap,		// 0D0
		  public TESIcon,					// 110
		  public TESWeightForm,				// 120
		  public BGSEquipType,				// 130
		  public BGSDestructibleObjectForm, // 140
		  public BGSPickupPutdownSounds,	// 150
		  public TESValueForm				// 168
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IngredientItem };
		inline static constexpr auto VTABLE{ VTABLE::IngredientItem };
		inline static constexpr auto FORM_TYPE{ FormType::kIngredient };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kUse = 1ui32 << 31
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kCostOverride = 1 << 0,
			kFoodItem = 1 << 1,
			kExtendDuration = 1 << 3,
			kReferencesPersist = 1 << 8
		};

		class GameData
		{
		public:
			// members
			std::uint16_t knownEffectFlags; // 00
			std::uint16_t playerUses;		// 02
		};
		static_assert(sizeof(GameData) == 0x04);

		// members
		MagicItem::Data data; // 178
		GameData gameData;	  // 180
	};
	static_assert(sizeof(IngredientItem) == 0x188);
}
