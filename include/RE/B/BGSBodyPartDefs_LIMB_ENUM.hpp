#pragma once

namespace RE::BGSBodyPartDefs
{
	enum class LIMB_ENUM : std::int32_t
	{
		kNone = -1,
		kTorso = 0,
		kHead1 = 1,
		kEye1 = 2,
		kLookAt1 = 3,
		kFlyGrab = 4,
		kHead2 = 5,
		kLeftArm1 = 6,
		kLeftArm2 = 7,
		kRightArm1 = 8,
		kRightArm2 = 9,
		kLeftLeg1 = 10,
		kLeftLeg2 = 11,
		kLeftLeg3 = 12,
		kRightLeg1 = 13,
		kRightLeg2 = 14,
		kRightLeg3 = 15,
		kBrain = 16,
		kWeapon = 17,
		kRoot = 18,
		kCom = 19,
		kPelvis = 20,
		kCamera = 21,
		kOffsetRoot = 22,
		kLeftFoot = 23,
		kRightFoot = 24,
		kFaceTargetSource = 25,

		kTotal = 26
	};
}
