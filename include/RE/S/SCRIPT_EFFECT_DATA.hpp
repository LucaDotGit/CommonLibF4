#pragma once

namespace RE
{
	class SCRIPT_EFFECT_DATA
	{
	public:
		// members
		bool scriptEffectStart;		 // 00
		bool scriptEffectFinish;	 // 01
		REX::Float32 secondsElapsed; // 04
	};
	static_assert(sizeof(SCRIPT_EFFECT_DATA) == 0x08);
}
