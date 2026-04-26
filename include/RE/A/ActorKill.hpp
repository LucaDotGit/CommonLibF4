#pragma once

namespace RE::ActorKill
{
	class Event
	{
	public:
		// members
		Actor* killer;
		Actor* victim;
	};
	static_assert(sizeof(Event) == 0x10);
}
