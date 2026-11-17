#pragma once

#include "RE/B/BGSCraftingUseSound.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESValueForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSComponent :
		public TESBoundObject,	   // 0x00
		public TESFullName,		   // 0x68
		public TESValueForm,	   // 0x78
		public BGSCraftingUseSound // 0x88
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSComponent;
		inline static constexpr const auto& VTABLE = VTABLE::BGSComponent;
		inline static constexpr auto FORM_TYPE = FormType::Component;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		TESObjectMISC* scrapItem;  // 0x98
		TESGlobal* modScrapScalar; // 0xA0
	};

	static_assert(sizeof(BGSComponent) == 0xA8);
}
