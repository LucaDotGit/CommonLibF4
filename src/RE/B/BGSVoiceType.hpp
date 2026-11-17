#pragma once

#include "RE/B/BSString.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/V/VOICE_TYPE_DATA.hpp"

namespace RE
{
	class __declspec(novtable) BGSVoiceType : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSVoiceType;
		inline static constexpr const auto& VTABLE = VTABLE::BGSVoiceType;
		inline static constexpr auto FORM_TYPE = FormType::VoiceType;

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
		VOICE_TYPE_DATA data;  // 0x20
		BSString formEditorID; // 0x28
	};

	static_assert(sizeof(BGSVoiceType) == 0x38);
}
