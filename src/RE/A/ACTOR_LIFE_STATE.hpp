#pragma once

namespace RE
{
	enum class ACTOR_LIFE_STATE : std::uint32_t
	{
		Alive = 0,
		Dying = 1,
		Dead = 2,
		Unconscious = 3,
		Reanimate = 4,
		Recycle = 5,
		Restrained = 6,
		EssentialDown = 7,
		Bleedout = 8
	};
}
