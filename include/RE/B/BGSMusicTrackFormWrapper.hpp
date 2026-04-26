#pragma once

#include "RE/B/BSIMusicTrack.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class BGSMusicTrack;

	class __declspec(novtable) BGSMusicTrackFormWrapper
		: public TESForm,	   // 00
		  public BSIMusicTrack // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMusicTrackFormWrapper };
		inline static constexpr auto VTABLE{ VTABLE::BGSMusicTrackFormWrapper };
		inline static constexpr auto FORM_TYPE{ FormType::kMusicTrack };

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
		BGSMusicTrack* trackImpl; // 30
	};
	static_assert(sizeof(BGSMusicTrackFormWrapper) == 0x38);
}
