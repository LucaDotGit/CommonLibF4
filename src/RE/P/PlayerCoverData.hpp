#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class PlayerCoverData
	{
	public:
		enum class PEEK_STATE : std::int32_t;

		// members
		NiPoint3 coverLocation;						   // 0x00
		NiPoint3 peekLocation;						   // 0x0C
		REX::Float32 peekTimer;						   // 0x18
		REX::Float32 updateTimer;					   // 0x2C
		REX::Float32 blockedTimer;					   // 0x20
		REX::Enum<PEEK_STATE, std::int32_t> peekState; // 0x24
		bool gunBlocked;							   // 0x28
	};

	static_assert(sizeof(PlayerCoverData) == 0x2C);
}
