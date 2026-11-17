#pragma once

namespace RE::TESAudio
{
	class SnapTransitionData
	{
	public:
		// members
		REX::Float32 transitionQuantum; // 0x00
		REX::Float32 desiredMult;		// 0x04
	};

	static_assert(sizeof(SnapTransitionData) == 0x08);
}
