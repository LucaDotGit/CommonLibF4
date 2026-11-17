#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiColorA.hpp"

namespace RE
{
	class FaderMenuDisplayState : public BSTValueEvent<NiColorA> // 0x00
	{
	public:
	};

	static_assert(sizeof(FaderMenuDisplayState) == 0x14);
}
