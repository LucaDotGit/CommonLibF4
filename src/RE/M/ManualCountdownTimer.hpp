#pragma once

namespace RE
{
	class ManualCountdownTimer
	{
	public:
		// members
		REX::Float32 timeRemaining; // 0x00
		REX::Float32 duration;		// 0x04
		bool active;				// 0x08
	};

	static_assert(sizeof(ManualCountdownTimer) == 0x0C);
}
