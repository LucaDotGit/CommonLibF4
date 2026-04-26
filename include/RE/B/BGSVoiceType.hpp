#pragma once

#include "RE/B/BSStringT.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/V/VOICE_TYPE_DATA.hpp"

namespace RE
{
	class __declspec(novtable) BGSVoiceType
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSVoiceType };
		inline static constexpr auto VTABLE{ VTABLE::BGSVoiceType };
		inline static constexpr auto FORM_TYPE{ FormType::kVoiceType };

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
		VOICE_TYPE_DATA data;  // 20
		BSString formEditorID; // 28
	};
	static_assert(sizeof(BGSVoiceType) == 0x38);
}
