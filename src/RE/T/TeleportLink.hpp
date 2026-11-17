#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class TeleportLink
	{
	public:
		// members
		TESObjectREFR* door;		   // 0x00
		NiPoint3 doorTeleportLocation; // 0x08
	};

	static_assert(sizeof(TeleportLink) == 0x18);
}
