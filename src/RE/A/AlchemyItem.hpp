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
	class __declspec(novtable) AlchemyItem :
		public MagicItem,				  // 0x000
		public BGSModelMaterialSwap,	  // 0x0D0
		public TESIcon,					  // 0x110
		public BGSMessageIcon,			  // 0x120
		public TESWeightForm,			  // 0x138
		public BGSEquipType,			  // 0x148
		public BGSDestructibleObjectForm, // 0x158
		public BGSPickupPutdownSounds,	  // 0x168
		public BGSCraftingUseSound,		  // 0x180
		public TESDescription			  // 0x190
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::AlchemyItem;
		inline static constexpr const auto& VTABLE = VTABLE::AlchemyItem;
		inline static constexpr auto FORM_TYPE = FormType::Potion;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				Medicine = 1 << 29
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class Data : public MagicItem::Data // 0x00
		{
		public:
			// members
			SpellItem* addictionItem;				  // 0x08
			REX::Float32 addictionChance;			  // 0x10
			BGSSoundDescriptorForm* consumptionSound; // 0x18
			BGSLocalizedString addictionName;		  // 0x20
		};

		static_assert(sizeof(Data) == 0x28);

		~AlchemyItem() override; // 0x00

		// members
		Data data;			 // 0x1A8
		TESIcon messageIcon; // 0x1D0
	};

	static_assert(sizeof(AlchemyItem) == 0x1E0);
}
