#pragma once

#include "RE/B/BSIMusicTrack.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class BGSMusicTrack;

	class __declspec(novtable) BGSMusicTrackFormWrapper :
		public TESForm,		 // 0x00
		public BSIMusicTrack // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMusicTrackFormWrapper;
		inline static constexpr const auto& VTABLE = VTABLE::BGSMusicTrackFormWrapper;
		inline static constexpr auto FORM_TYPE = FormType::MusicTrack;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~BGSMusicTrackFormWrapper() override; // 0x00

		// members
		BGSMusicTrack* trackImpl; // 0x30
	};

	static_assert(sizeof(BGSMusicTrackFormWrapper) == 0x38);
}
