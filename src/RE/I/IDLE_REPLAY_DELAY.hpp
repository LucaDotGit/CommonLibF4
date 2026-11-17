#pragma once

namespace RE
{
	class IDLE_REPLAY_DELAY
	{
	public:
		// memberse
		TESIdleForm* idleForm; // 0x00
		REX::Float32 delay;	   // 0x08
	};

	static_assert(sizeof(IDLE_REPLAY_DELAY) == 0x10);
}
