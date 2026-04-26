#pragma once

#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class ReanimateData
	{
	public:
		// members
		ActorHandle caster;		   // 00
		MagicItem* reanimateSpell; // 08
	};
	static_assert(sizeof(ReanimateData) == 0x10);
}
