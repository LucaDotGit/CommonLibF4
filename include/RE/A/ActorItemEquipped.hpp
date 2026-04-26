#pragma once

namespace RE::ActorItemEquipped
{
	class Event
	{
	public:
		// members
		TESBoundObject* item; // 00
		Actor* equipper;	  // 08
	};
	static_assert(sizeof(Event) == 0x10);
}
