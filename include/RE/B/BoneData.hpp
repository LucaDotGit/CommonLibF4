#pragma once

#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class BoneData
	{
	public:
		// members
		NiMatrix3 localBoneRotation;				// 00
		NiPoint3 worldBoneDir;						// 30
		std::uint32_t parentWorldBoneRotationIndex; // 3C
	};
	static_assert(sizeof(BoneData) == 0x40);
}
