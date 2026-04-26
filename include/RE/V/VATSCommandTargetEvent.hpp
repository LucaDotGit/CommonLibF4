#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class VATSCommandTargetEvent
		: public BSTValueEvent<ObjectRefHandle> // 00
	{
	public:
	};
	static_assert(sizeof(VATSCommandTargetEvent) == 0x08);
}
