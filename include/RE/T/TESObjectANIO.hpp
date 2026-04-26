#pragma once

#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) TESObjectANIO
		: public TESForm,			  // 00
		  public BGSModelMaterialSwap // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectANIO };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectANIO };
		inline static constexpr auto FORM_TYPE{ FormType::kAnimObject };

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
		BSFixedString formEditorID;	   // 60
		BSFixedString unloadEventName; // 68
	};
	static_assert(sizeof(TESObjectANIO) == 0x70);
}
