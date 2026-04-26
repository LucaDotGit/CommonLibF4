#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class HUDDirectionalHitIndicatorData
	{
	public:
		// members
		std::uint64_t timeOutOccurred; // 00
		REX::Float32 angleToPlayer;	   // 08
		REX::Float32 calculatedAlpha;  // 0C
		ActorHandle whoHitMe;		   // 10
		bool isNew;					   // 14
	};
	static_assert(sizeof(HUDDirectionalHitIndicatorData) == 0x18);
}
