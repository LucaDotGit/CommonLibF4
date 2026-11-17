#pragma once

#include "RE/B/BSSoundHandle.hpp"

namespace RE
{
	class BGSAwakeSoundData
	{
	public:
		enum class State : std::int32_t
		{
			Playing = 0,
			Paused = 1,
			Stopped = 2,

			_Count = 3
		};

		// members
		BSSoundHandle sound;				  // 0x00
		std::uint32_t soundFormID;			  // 0x08
		REX::Float32 volume;				  // 0x0C
		REX::Enum<State, std::int32_t> state; // 0x10
	};

	static_assert(sizeof(BGSAwakeSoundData) == 0x14);
}
