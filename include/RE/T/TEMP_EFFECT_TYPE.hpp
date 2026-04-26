#pragma once

namespace RE
{
	enum class TEMP_EFFECT_TYPE : std::int32_t
	{
		kTerrain = 0,
		kWeaponBlood = 1,
		kDecal = 2,
		kGeometryDecal = 3,
		kParticle = 4,
		kDebris = 5,
		kSPG = 6,
		kDefault = 7,
		kRefDefault = 8,
		kRefModel = 9,
		kRefShader = 10,
		kMagicSummon = 11
	};
}
