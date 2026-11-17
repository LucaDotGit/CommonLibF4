#pragma once

#include "RE/N/NiAnimationKey.hpp"
#include "RE/N/NiColorA.hpp"

namespace RE
{
	class NiColorKey : public NiAnimationKey // 0x00
	{
	public:
		// members
		NiColorA value; // 0x00
	};

	static_assert(sizeof(NiColorKey) == 0x14);
}
