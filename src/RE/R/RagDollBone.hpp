#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class RagDollBone
	{
	public:
		// members
		char boneID;	  // 0x00
		NiPoint3 bonePos; // 0x04
		NiPoint3 boneRot; // 0x10
	};

	static_assert(sizeof(RagDollBone) == 0x1C);
}
