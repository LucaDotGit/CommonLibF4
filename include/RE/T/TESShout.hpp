#pragma once

#include "RE/B/BGSEquipType.hpp"
#include "RE/B/BGSMenuDisplayObject.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class __declspec(novtable) TESShout
		: public TESForm,			   // 00
		  public TESFullName,		   // 20
		  public BGSMenuDisplayObject, // 30
		  public BGSEquipType,		   // 40
		  public TESDescription		   // 50
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESShout };
		inline static constexpr auto VTABLE{ VTABLE::TESShout };
		inline static constexpr auto FORM_TYPE{ FormType::kShout };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class VariationID : std::uint32_t
		{
			kNone = static_cast<std::underlying_type_t<VariationID>>(-1),
			kOne = 0,
			kTwo = 1,
			kThree = 2,

			kTotal = 3
		};

		class Variation
		{
		public:
			// members
			TESWordOfPower* word;	   // 00
			SpellItem* spell;		   // 08
			REX::Float32 recoveryTime; // 10
		};
		static_assert(sizeof(Variation) == 0x18);

		// members
		std::array<Variation, std::to_underlying(VariationID::kTotal)> variations; // 68
	};
	static_assert(sizeof(TESShout) == 0xB0);
}
