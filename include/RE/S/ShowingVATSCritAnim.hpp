#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class ShowingVATSCritAnim
		: public BSTValueEvent<bool> // 00
	{
	public:
	};
	static_assert(sizeof(ShowingVATSCritAnim) == 0x02);
}
