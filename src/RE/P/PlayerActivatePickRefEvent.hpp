#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class PlayerActivatePickRefEvent : public BSTValueEvent<ObjectRefHandle> // 0x00
	{
	public:
	};

	static_assert(sizeof(PlayerActivatePickRefEvent) == 0x08);
}
