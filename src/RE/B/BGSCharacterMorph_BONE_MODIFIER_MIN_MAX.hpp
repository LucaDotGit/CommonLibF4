#pragma once

namespace RE::BGSCharacterMorph
{
	class BONE_MODIFIER_MIN_MAX
	{
	public:
		// members
		REX::Float32 minY; // 0x00
		REX::Float32 minZ; // 0x04
		REX::Float32 maxY; // 0x08
		REX::Float32 maxZ; // 0x0C
	};

	static_assert(sizeof(BONE_MODIFIER_MIN_MAX) == 0x10);
}
