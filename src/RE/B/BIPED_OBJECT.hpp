#pragma once

namespace RE
{
	enum class BIPED_OBJECT : std::int32_t
	{
		None = -1,
		HairTop = 0,
		HairLong = 1,
		FaceGenHead = 2,
		Body = 3,
		LeftHand = 4,
		RightHand = 5,
		UnderTorso = 6,
		UnderLeftArm = 7,
		UnderRightArm = 8,
		UnderLeftLeg = 9,
		UnderRightLeg = 10,
		AboveTorso = 11,
		AboveLeftArm = 12,
		AboveRightArm = 13,
		AboveLeftLeg = 14,
		AboveRightLeg = 15,
		Headband = 16,
		Eyes = 17,
		Beard = 18,
		Mouth = 19,
		Neck = 20,
		Ring = 21,
		Scalp = 22,
		Decapitation = 23,
		Unnamed1 = 24,
		Unnamed2 = 25,
		Unnamed3 = 26,
		Unnamed4 = 27,
		Unnamed5 = 28,
		Shield = 29,
		Pipboy = 30,
		FX = 31,

		EditorTotal = 32,

		WeaponHand = EditorTotal,
		WeaponSword = 33,
		WeaponDagger = 34,
		WeaponAxe = 35,
		WeaponMace = 36,
		WeaponTwoHandMelee = 37,
		WeaponBow = 38,
		WeaponStaff = 39,
		Quiver = 40,
		WeaponGun = 41,
		WeaponGrenade = 42,
		WeaponMine = 43,

		_Count = 44
	};
}
