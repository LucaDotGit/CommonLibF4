#pragma once

namespace RE
{
	class BGSHazardData
	{
	public:
		enum class BGSHazardFlags : std::uint32_t
		{
			kNone = 0,
			kPlayerOnly = 1 << 0,
			kInheritDuration = 1 << 1,
			kAlignToNormal = 1 << 2,
			kInheritRadius = 1 << 3,
			kDropToGround = 1 << 4,
			kTaperEffectiveness = 1 << 5
		};

		// members
		std::uint32_t limit;							   // 00
		REX::Float32 radius;							   // 04
		REX::Float32 lifetime;							   // 08
		REX::Float32 imageSpaceRadius;					   // 0C
		REX::Float32 targetInterval;					   // 10
		REX::EnumSet<BGSHazardFlags, std::uint32_t> flags; // 14
		SpellItem* spell;								   // 18
		TESObjectLIGH* light;							   // 20
		BGSImpactDataSet* impactDataSet;				   // 28
		BGSSoundDescriptorForm* sound;					   // 30
		REX::Float32 fullEffectRadius;					   // 38
		REX::Float32 taperWeight;						   // 3C
		REX::Float32 taperCurve;						   // 40
	};
	static_assert(sizeof(BGSHazardData) == 0x48);
}
