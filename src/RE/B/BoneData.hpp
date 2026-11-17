#pragma once

#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BoneData
	{
	public:
		// members
		NiMatrix3 localBoneRotation;				// 0x00
		NiPoint3 worldBoneDir;						// 0x30
		std::uint32_t parentWorldBoneRotationIndex; // 0x3C
	};

	static_assert(sizeof(BoneData) == 0x40);
}
