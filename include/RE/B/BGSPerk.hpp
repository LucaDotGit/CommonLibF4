#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/P/PerkData.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESIcon.hpp"

namespace RE
{
	class BGSPerkEntry;

	class __declspec(novtable) BGSPerk
		: public TESForm,		 // 00
		  public TESFullName,	 // 20
		  public TESDescription, // 30
		  public TESIcon		 // 48
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSPerk };
		inline static constexpr auto VTABLE{ VTABLE::BGSPerk };
		inline static constexpr auto FORM_TYPE{ FormType::kPerk };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kNonPlayable = 1 << 2,
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		PerkData data;						 // 58
		TESCondition perkConditions;		 // 60
		BSTArray<BGSPerkEntry*> perkEntries; // 68
		BGSPerk* nextPerk;					 // 80
		BGSSoundDescriptorForm* sound;		 // 88
		BSFixedStringCS swfFile;			 // 90
	};
	static_assert(sizeof(BGSPerk) == 0x98);
}
