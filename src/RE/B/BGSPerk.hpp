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

	class __declspec(novtable) BGSPerk :
		public TESForm,		   // 0x00
		public TESFullName,	   // 0x20
		public TESDescription, // 0x30
		public TESIcon		   // 0x48
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSPerk;
		inline static constexpr const auto& VTABLE = VTABLE::BGSPerk;
		inline static constexpr auto FORM_TYPE = FormType::Perk;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				NonPlayable = 1 << 2,
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		PerkData data;						 // 0x58
		TESCondition perkConditions;		 // 0x60
		BSTArray<BGSPerkEntry*> perkEntries; // 0x68
		BGSPerk* nextPerk;					 // 0x80
		BGSSoundDescriptorForm* sound;		 // 0x88
		BSFixedStringCS swfFile;			 // 0x90
	};

	static_assert(sizeof(BGSPerk) == 0x98);
}
