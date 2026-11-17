#pragma once

namespace RE::ActorItemEquipped
{
	class Event
	{
	public:
		// members
		TESBoundObject* item; // 0x00
		Actor* equipper;	  // 0x08
	};

	static_assert(sizeof(Event) == 0x10);
}
