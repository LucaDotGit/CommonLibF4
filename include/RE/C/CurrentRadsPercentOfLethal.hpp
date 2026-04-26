#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class CurrentRadsPercentOfLethal
		: public BSTValueEvent<REX::Float32> // 00
	{
	public:
	};
	static_assert(sizeof(CurrentRadsPercentOfLethal) == 0x08);
}
