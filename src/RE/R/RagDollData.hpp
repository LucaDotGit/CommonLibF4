#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class RagDollBone;

	class RagDollData
	{
	public:
		// members
		std::uint8_t boneCount; // 0x00
		RagDollBone* boneArray; // 0x08
		NiPoint3 bip01Rot;		// 0x10
	};

	static_assert(sizeof(RagDollData) == 0x20);
}
