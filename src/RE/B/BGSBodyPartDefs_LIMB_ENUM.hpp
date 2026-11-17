#pragma once

namespace RE::BGSBodyPartDefs
{
	enum class LIMB_ENUM : std::int32_t
	{
		None = -1,
		Torso = 0,
		Head1 = 1,
		Eye1 = 2,
		LookAt1 = 3,
		FlyGrab = 4,
		Head2 = 5,
		LeftArm1 = 6,
		LeftArm2 = 7,
		RightArm1 = 8,
		RightArm2 = 9,
		LeftLeg1 = 10,
		LeftLeg2 = 11,
		LeftLeg3 = 12,
		RightLeg1 = 13,
		RightLeg2 = 14,
		RightLeg3 = 15,
		Brain = 16,
		Weapon = 17,
		Root = 18,
		Com = 19,
		Pelvis = 20,
		Camera = 21,
		OffsetRoot = 22,
		LeftFoot = 23,
		RightFoot = 24,
		FaceTargetSource = 25,

		_Count = 26
	};
}
