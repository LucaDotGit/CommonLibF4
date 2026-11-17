#pragma once

#include "RE/B/BGSAimModel.hpp"
#include "RE/B/BSSpring_SpringState.hpp"
#include "RE/N/NiPoint2.hpp"

namespace RE
{
	class __declspec(novtable) AimModel
	{
	public:
		// members
		BGSAimModel::Data aimModelData;						  // 0x00
		BSSpring::SpringState<NiPoint2> recoilSpring;		  // 0x40
		BSSpring::SpringState<NiPoint2> recoilDiminishSpring; // 0x54
		NiPoint2 targetRecoilHead;							  // 0x68
		NiPoint2 currentRecoilHead;							  // 0x70
		NiPoint2 prevRecoilRad;								  // 0x78
		NiPoint2 preShotAimRad;								  // 0x80
		Actor* actor;										  // 0x88
		REX::Float32 fireConeSize;							  // 0x90
		REX::Float32 lastShotDeltaMs;						  // 0x94
		std::uint32_t continuousShots;						  // 0x98
	};

	static_assert(sizeof(AimModel) == 0xA0);
}
