#pragma once

namespace RE::TESAudio
{
	class SnapTransitionData
	{
	public:
		// members
		REX::Float32 transitionQuantum; // 00
		REX::Float32 desiredMult;		// 04
	};
	static_assert(sizeof(SnapTransitionData) == 0x08);
}
