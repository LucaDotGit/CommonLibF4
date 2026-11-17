#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIMusicType.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSMusicType :
		public TESForm,		// 0x00
		public BSIMusicType // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMusicType;
		inline static constexpr const auto& VTABLE = VTABLE::BGSMusicType;
		inline static constexpr auto FORM_TYPE = FormType::MusicType;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				UsesPalette = 1 << 20
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BSFixedString formEditorID; // 0x70
	};

	static_assert(sizeof(BGSMusicType) == 0x78);
}
