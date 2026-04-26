#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class PlayerCoverData
	{
	public:
		enum class PEEK_STATE : std::int32_t;

		// members
		NiPoint3 coverLocation;						   // 00
		NiPoint3 peekLocation;						   // 0C
		REX::Float32 peekTimer;						   // 18
		REX::Float32 updateTimer;					   // 2C
		REX::Float32 blockedTimer;					   // 20
		REX::Enum<PEEK_STATE, std::int32_t> peekState; // 24
		bool gunBlocked;							   // 28
	};
	static_assert(sizeof(PlayerCoverData) == 0x2C);
}
