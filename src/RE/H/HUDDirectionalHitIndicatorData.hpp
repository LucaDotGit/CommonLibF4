#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class HUDDirectionalHitIndicatorData
	{
	public:
		// members
		std::uint64_t timeOutOccurred; // 0x00
		REX::Float32 angleToPlayer;	   // 0x08
		REX::Float32 calculatedAlpha;  // 0x0C
		ActorHandle whoHitMe;		   // 0x10
		bool isNew;					   // 0x14
	};

	static_assert(sizeof(HUDDirectionalHitIndicatorData) == 0x18);
}
