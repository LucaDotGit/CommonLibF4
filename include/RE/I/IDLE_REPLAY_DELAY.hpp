#pragma once

namespace RE
{
	class IDLE_REPLAY_DELAY
	{
	public:
		// memberse
		TESIdleForm* idleForm; // 00
		REX::Float32 delay;	   // 08
	};
	static_assert(sizeof(IDLE_REPLAY_DELAY) == 0x10);
}
