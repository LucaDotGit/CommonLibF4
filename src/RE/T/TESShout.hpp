#pragma once

#include "RE/B/BGSEquipType.hpp"
#include "RE/B/BGSMenuDisplayObject.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class __declspec(novtable) TESShout :
		public TESForm,				 // 0x00
		public TESFullName,			 // 0x20
		public BGSMenuDisplayObject, // 0x30
		public BGSEquipType,		 // 0x40
		public TESDescription		 // 0x50
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESShout;
		inline static constexpr const auto& VTABLE = VTABLE::TESShout;
		inline static constexpr auto FORM_TYPE = FormType::Shout;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class VariationID : std::int32_t
		{
			None = -1,
			One = 0,
			Two = 1,
			Three = 2,

			_Count = 3
		};

		class Variation
		{
		public:
			// members
			TESWordOfPower* word;	   // 0x00
			SpellItem* spell;		   // 0x08
			REX::Float32 recoveryTime; // 0x10
		};

		static_assert(sizeof(Variation) == 0x18);

		// members
		std::array<Variation, std::to_underlying(VariationID::_Count)> variations; // 0x68
	};

	static_assert(sizeof(TESShout) == 0xB0);
}
