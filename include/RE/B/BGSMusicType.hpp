#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIMusicType.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSMusicType
		: public TESForm,	  // 00
		  public BSIMusicType // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMusicType };
		inline static constexpr auto VTABLE{ VTABLE::BGSMusicType };
		inline static constexpr auto FORM_TYPE{ FormType::kMusicType };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kUsesPalette = 1 << 20
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BSFixedString formEditorID; // 70
	};
	static_assert(sizeof(BGSMusicType) == 0x78);
}
