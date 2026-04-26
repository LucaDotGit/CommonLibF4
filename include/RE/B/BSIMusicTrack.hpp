#pragma once

namespace RE
{
	class __declspec(novtable) BSIMusicTrack
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSIMusicTrack };
		inline static constexpr auto VTABLE{ VTABLE::BSIMusicTrack };

		enum class MUSIC_STATUS : std::int32_t;

		virtual ~BSIMusicTrack() = default; // 00

		// add
		virtual void DoUpdate() = 0;										  // 01
		virtual void DoPlay() = 0;											  // 02
		virtual void DoPause() = 0;											  // 03
		virtual void DoFinish(bool a_immediate, REX::Float32 a_fadeTime) = 0; // 04
		virtual REX::Float32 GetDurationImpl() const = 0;					  // 05
		virtual std::uint32_t GetType() const = 0;							  // 06
		virtual bool TestCanPlay() const;									  // 07 - { return true; }
		virtual MUSIC_STATUS GetMusicStatus() const;						  // 08 - { return *trackStatus; }
		virtual void DoSetDuckingAttenuation(std::uint16_t a_ducking);		  // 09 - { return; }
		virtual void DoClearDucking();										  // 0A - { return; }

		// members
		REX::Enum<MUSIC_STATUS, std::int32_t> trackStatus; // 08
	};
	static_assert(sizeof(BSIMusicTrack) == 0x10);
}
