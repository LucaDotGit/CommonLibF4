#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/S/ShowRolloverParameters.hpp"

namespace RE
{
	class HUDRolloverStateEvent : public BSTValueEvent<ShowRolloverParameters> // 0x00
	{
	};

	static_assert(sizeof(HUDRolloverStateEvent) == 0x30);
}
