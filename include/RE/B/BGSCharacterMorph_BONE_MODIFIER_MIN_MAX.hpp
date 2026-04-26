#pragma once

namespace RE::BGSCharacterMorph
{
	class BONE_MODIFIER_MIN_MAX
	{
	public:
		// members
		REX::Float32 minY; // 00
		REX::Float32 minZ; // 04
		REX::Float32 maxY; // 08
		REX::Float32 maxZ; // 0C
	};
	static_assert(sizeof(BONE_MODIFIER_MIN_MAX) == 0x10);
}
