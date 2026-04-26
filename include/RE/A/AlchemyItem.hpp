#pragma once

#include "RE/B/BGSCraftingUseSound.hpp"
#include "RE/B/BGSDestructibleObjectForm.hpp"
#include "RE/B/BGSEquipType.hpp"
#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BGSMessageIcon.hpp"
#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BGSPickupPutdownSounds.hpp"
#include "RE/M/MagicItem.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESIcon.hpp"
#include "RE/T/TESWeightForm.hpp"

namespace RE
{
	class __declspec(novtable) AlchemyItem
		: public MagicItem,					// 000
		  public BGSModelMaterialSwap,		// 0D0
		  public TESIcon,					// 110
		  public BGSMessageIcon,			// 120
		  public TESWeightForm,				// 138
		  public BGSEquipType,				// 148
		  public BGSDestructibleObjectForm, // 158
		  public BGSPickupPutdownSounds,	// 168
		  public BGSCraftingUseSound,		// 180
		  public TESDescription				// 190
	{
	public:
		inline static constexpr auto RTTI{ RTTI::AlchemyItem };
		inline static constexpr auto VTABLE{ VTABLE::AlchemyItem };
		inline static constexpr auto FORM_TYPE{ FormType::kPotion };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kMedicine = 1 << 29
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class Data
			: public MagicItem::Data // 00
		{
		public:
			// members
			SpellItem* addictionItem;				  // 08
			REX::Float32 addictionChance;			  // 10
			BGSSoundDescriptorForm* consumptionSound; // 18
			BGSLocalizedString addictionName;		  // 20
		};
		static_assert(sizeof(Data) == 0x28);

		// members
		Data data;			 // 1A8
		TESIcon messageIcon; // 1D0
	};
	static_assert(sizeof(AlchemyItem) == 0x1E0);
}
