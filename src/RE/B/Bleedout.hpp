#pragma once

namespace RE::Bleedout
{
	class Event
	{
	public:
		// members
		Actor* actorBleedingOut; // 0x00
	};

	static_assert(sizeof(Event) == 0x08);
}
