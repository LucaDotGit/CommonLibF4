#pragma once

namespace RE
{
	class ManualCountdownTimer
	{
	public:
		// members
		REX::Float32 timeRemaining; // 00
		REX::Float32 duration;		// 04
		bool active;				// 08
	};
	static_assert(sizeof(ManualCountdownTimer) == 0x0C);
}
