#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiColor.hpp"

namespace RE
{
	class FaderMenuDisplayState
		: public BSTValueEvent<NiColorA> // 00
	{
	public:
	};
	static_assert(sizeof(FaderMenuDisplayState) == 0x14);
}
