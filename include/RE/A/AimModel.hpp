#pragma once

#include "RE/B/BGSAimModel.hpp"
#include "RE/B/BSSpring_SpringState.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class __declspec(novtable) AimModel
	{
	public:
		// members
		BGSAimModel::Data aimModelData;						  // 00
		BSSpring::SpringState<NiPoint2> recoilSpring;		  // 40
		BSSpring::SpringState<NiPoint2> recoilDiminishSpring; // 54
		NiPoint2 targetRecoilHead;							  // 68
		NiPoint2 currentRecoilHead;							  // 70
		NiPoint2 prevRecoilRad;								  // 78
		NiPoint2 preShotAimRad;								  // 80
		Actor* actor;										  // 88
		REX::Float32 fireConeSize;							  // 90
		REX::Float32 lastShotDeltaMs;						  // 94
		std::uint32_t continuousShots;						  // 98
	};
	static_assert(sizeof(AimModel) == 0xA0);
}
