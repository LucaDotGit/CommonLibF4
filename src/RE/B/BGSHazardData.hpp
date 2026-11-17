#pragma once

namespace RE
{
	class BGSHazardData
	{
	public:
		enum class BGSHazardFlags : std::uint32_t
		{
			None = 0,
			PlayerOnly = 1 << 0,
			InheritDuration = 1 << 1,
			AlignToNormal = 1 << 2,
			InheritRadius = 1 << 3,
			DropToGround = 1 << 4,
			TaperEffectiveness = 1 << 5
		};

		// members
		std::uint32_t limit;							   // 0x00
		REX::Float32 radius;							   // 0x04
		REX::Float32 lifetime;							   // 0x08
		REX::Float32 imageSpaceRadius;					   // 0x0C
		REX::Float32 targetInterval;					   // 0x10
		REX::EnumSet<BGSHazardFlags, std::uint32_t> flags; // 0x14
		SpellItem* spell;								   // 0x18
		TESObjectLIGH* light;							   // 0x20
		BGSImpactDataSet* impactDataSet;				   // 0x28
		BGSSoundDescriptorForm* sound;					   // 0x30
		REX::Float32 fullEffectRadius;					   // 0x38
		REX::Float32 taperWeight;						   // 0x3C
		REX::Float32 taperCurve;						   // 0x40
	};

	static_assert(sizeof(BGSHazardData) == 0x48);
}
