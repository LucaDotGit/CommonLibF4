#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class __declspec(novtable) BSIMusicTrack
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSIMusicTrack;
		inline static constexpr const auto& VTABLE = VTABLE::BSIMusicTrack;

		enum class MUSIC_STATUS : std::int32_t;

		virtual ~BSIMusicTrack() = default; // 0x00

		// add
		virtual void DoUpdate() = 0;										  // 0x01
		virtual void DoPlay() = 0;											  // 0x02
		virtual void DoPause() = 0;											  // 0x03
		virtual void DoFinish(bool a_immediate, REX::Float32 a_fadeTime) = 0; // 0x04
		virtual auto GetDurationImpl() const -> REX::Float32 = 0;			  // 0x05
		virtual auto GetType() const -> std::uint32_t = 0;					  // 0x06
		virtual auto TestCanPlay() const -> bool;							  // 0x07 - { return true; }
		virtual auto GetMusicStatus() const -> MUSIC_STATUS;				  // 0x08 - { return *trackStatus; }
		virtual void DoSetDuckingAttenuation(std::uint16_t a_ducking);		  // 0x09 - { return; }
		virtual void DoClearDucking();										  // 0x0A - { return; }

		GAME_HEAP_REDEFINE_NEW(BSIMusicTrack);

		// members
		REX::Enum<MUSIC_STATUS, std::int32_t> trackStatus; // 0x08
	};

	static_assert(sizeof(BSIMusicTrack) == 0x10);
}
