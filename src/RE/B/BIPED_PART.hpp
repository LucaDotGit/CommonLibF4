#pragma once

namespace RE
{
	enum class BIPED_PART : std::int32_t
	{
		Other = 0,
		Head = 1,
		Body = 2,
		Spine1 = 3,
		Spine2 = 4,
		LUpperArm = 5,
		LForearm = 6,
		LHand = 7,
		LThigh = 8,
		LCalf = 9,
		LFoot = 10,
		RUpperArm = 11,
		RForearm = 12,
		RHand = 13,
		RThigh = 14,
		RCalf = 15,
		RFoot = 16,
		Tail = 17,
		Shield = 18,
		Quiver = 19,
		Weapon = 20,
		Ponytail = 21,
		Wing = 22,
		Pack = 23,
		Chain = 24,
		AddonHead = 25,
		AddonChest = 26,
		AddonLeg = 27,
		AddonArm = 28,

		_Count = 32
	};
}
