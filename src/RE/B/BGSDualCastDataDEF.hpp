#pragma once

namespace RE
{
	class BGSDualCastDataDEF
	{
	public:
		// members
		BGSProjectile* projectile;		 // 0x00
		BGSExplosion* explosion;		 // 0x08
		TESEffectShader* effectShader;	 // 0x10
		BGSArtObject* hitEffectArt;		 // 0x18
		BGSImpactDataSet* impactDataSet; // 0x20
		std::uint32_t flags;			 // 0x28
	};

	static_assert(sizeof(BGSDualCastDataDEF) == 0x30);
}
