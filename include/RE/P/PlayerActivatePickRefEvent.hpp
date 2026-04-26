#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class PlayerActivatePickRefEvent
		: public BSTValueEvent<ObjectRefHandle> // 00
	{
	};
	static_assert(sizeof(PlayerActivatePickRefEvent) == 0x08);
}
