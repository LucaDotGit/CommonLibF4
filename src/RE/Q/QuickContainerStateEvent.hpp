#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/Q/QuickContainerStateData.hpp"

namespace RE
{
	class QuickContainerStateEvent : public BSTValueEvent<QuickContainerStateData> // 0x00
	{
	public:
	};

	static_assert(sizeof(QuickContainerStateEvent) == 0xC0);
}
