#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class TeleportLink
	{
	public:
		// members
		TESObjectREFR* door;		   // 00
		NiPoint3 doorTeleportLocation; // 08
	};
	static_assert(sizeof(TeleportLink) == 0x18);
}
