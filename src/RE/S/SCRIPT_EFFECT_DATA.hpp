#pragma once

namespace RE
{
	class SCRIPT_EFFECT_DATA
	{
	public:
		// members
		bool scriptEffectStart;		 // 0x00
		bool scriptEffectFinish;	 // 0x01
		REX::Float32 secondsElapsed; // 0x04
	};

	static_assert(sizeof(SCRIPT_EFFECT_DATA) == 0x08);
}
