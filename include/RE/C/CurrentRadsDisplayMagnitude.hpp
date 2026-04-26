#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class CurrentRadsDisplayMagnitude
		: public BSTValueEvent<REX::Float32> // 00
	{
	public:
	};
	static_assert(sizeof(CurrentRadsDisplayMagnitude) == 0x08);
}
