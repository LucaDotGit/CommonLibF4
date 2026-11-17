#pragma once

#include "RE/B/BSIMusicTrack.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class __declspec(novtable) BSIMusicType
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSIMusicType;
		inline static constexpr const auto& VTABLE = VTABLE::BSIMusicType;

		// add
		virtual void DoUpdate() = 0;									 // 0x00
		virtual void DoPlay() = 0;										 // 0x01
		virtual void DoPause() = 0;										 // 0x02
		virtual void DoFinish(bool a_immediate) = 0;					 // 0x03
		virtual void DoApplyDuckingAttenuation(std::uint16_t a_ducking); // 0x04 - { return; }
		virtual void DoClearDucking();									 // 0x05 - { return; }
		virtual void DoPrepare();										 // 0x06 - { return; }

		virtual ~BSIMusicType(); // 0x07

		// members
		std::uint32_t flags;											 // 0x08 - To-Do
		std::uint8_t priority;											 // 0x0C
		std::uint8_t padding;											 // 0x0D
		std::uint16_t ducksOtherMusicBy;								 // 0x0E
		REX::Float32 fadeTime;											 // 0x10
		std::uint32_t currentTrackIndex;								 // 0x14
		BSTArray<std::uint32_t> trackHistory;							 // 0x18
		BSTArray<BSIMusicTrack*> tracks;								 // 0x30
		REX::Enum<BSIMusicTrack::MUSIC_STATUS, std::int32_t> typeStatus; // 0x48
	};

	static_assert(sizeof(BSIMusicType) == 0x50);
}
