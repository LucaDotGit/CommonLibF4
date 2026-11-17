#pragma once

#include "RE/H/hkPadSpu.hpp"

namespace RE
{
	class hkStepInfo
	{
	public:
		// members
		hkPadSpu<REX::Float32> startTime;	 // 0x00
		hkPadSpu<REX::Float32> endTime;		 // 0x04
		hkPadSpu<REX::Float32> deltaTime;	 // 0x08
		hkPadSpu<REX::Float32> invDeltaTime; // 0x0C
	};

	static_assert(sizeof(hkStepInfo) == 0x10);
}
