#pragma once

#include "RE/B/BSIMusicTrack.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) BSIMusicType
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSIMusicType };
		inline static constexpr auto VTABLE{ VTABLE::BSIMusicType };

		// add
		virtual void DoUpdate() = 0;									 // 00
		virtual void DoPlay() = 0;										 // 01
		virtual void DoPause() = 0;										 // 02
		virtual void DoFinish(bool a_immediate) = 0;					 // 03
		virtual void DoApplyDuckingAttenuation(std::uint16_t a_ducking); // 04 - { return; }
		virtual void DoClearDucking();									 // 05 - { return; }
		virtual void DoPrepare();										 // 06 - { return; }

		virtual ~BSIMusicType(); // 07

		// members
		std::uint32_t flags;											 // 08 - TODO
		std::uint8_t priority;											 // 0C
		std::uint8_t padding;											 // 0D
		std::uint16_t ducksOtherMusicBy;								 // 0E
		REX::Float32 fadeTime;											 // 10
		std::uint32_t currentTrackIndex;								 // 14
		BSTArray<std::uint32_t> trackHistory;							 // 18
		BSTArray<BSIMusicTrack*> tracks;								 // 30
		REX::Enum<BSIMusicTrack::MUSIC_STATUS, std::int32_t> typeStatus; // 48
	};
	static_assert(sizeof(BSIMusicType) == 0x50);
}
