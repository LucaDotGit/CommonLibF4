#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class ReanimateData
	{
	public:
		// members
		ActorHandle caster;		   // 0x00
		MagicItem* reanimateSpell; // 0x08
	};

	static_assert(sizeof(ReanimateData) == 0x10);
}
