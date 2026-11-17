#pragma once

namespace RE
{
	enum class TEMP_EFFECT_TYPE : std::int32_t
	{
		Terrain = 0,
		WeaponBlood = 1,
		Decal = 2,
		GeometryDecal = 3,
		Particle = 4,
		Debris = 5,
		SPG = 6,
		Default = 7,
		RefDefault = 8,
		RefModel = 9,
		RefShader = 10,
		MagicSummon = 11
	};
}
