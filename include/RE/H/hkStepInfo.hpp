#pragma once

#include "RE/H/hkPadSpu.hpp"

namespace RE
{
	class hkStepInfo
	{
	public:
		// members
		hkPadSpu<REX::Float32> startTime;	 // 00
		hkPadSpu<REX::Float32> endTime;		 // 04
		hkPadSpu<REX::Float32> deltaTime;	 // 08
		hkPadSpu<REX::Float32> invDeltaTime; // 0C
	};
	static_assert(sizeof(hkStepInfo) == 0x10);
}
