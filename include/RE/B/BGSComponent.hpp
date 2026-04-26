#pragma once

#include "RE/B/BGSCraftingUseSound.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESValueForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSComponent
		: public TESBoundObject,	 // 00
		  public TESFullName,		 // 68
		  public TESValueForm,		 // 78
		  public BGSCraftingUseSound // 88
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSComponent };
		inline static constexpr auto VTABLE{ VTABLE::BGSComponent };
		inline static constexpr auto FORM_TYPE{ FormType::kComponent };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		TESObjectMISC* scrapItem;  // 98
		TESGlobal* modScrapScalar; // 90
	};
	static_assert(sizeof(BGSComponent) == 0xA8);
}
