#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/P/PlayerActiveEffectIcons.hpp"

namespace RE
{
	class PlayerActiveEffectIconsEvent
		: public BSTValueEvent<PlayerActiveEffectIcons> // 00
	{
	public:
	};
	static_assert(sizeof(PlayerActiveEffectIconsEvent) == 0x28);
}
