#pragma once

#include "RE/B/BSSoundHandle.hpp"

namespace RE
{
	class BGSAwakeSoundData
	{
	public:
		enum class State : std::int32_t
		{
			kPlaying = 0,
			kPaused = 1,
			kStopped = 2,

			kTotal = 3
		};

		// members
		BSSoundHandle sound;				  // 00
		std::uint32_t soundFormID;			  // 08
		REX::Float32 volume;				  // 0C
		REX::Enum<State, std::int32_t> state; // 10
	};
	static_assert(sizeof(BGSAwakeSoundData) == 0x14);
}
