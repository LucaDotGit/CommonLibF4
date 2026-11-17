#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/S/SaveLoadMessageStringData.hpp"

namespace RE
{
	class SaveLoadMessageStringEvent : public BSTValueEvent<SaveLoadMessageStringData> // 0x00
	{
	public:
	};

	static_assert(sizeof(SaveLoadMessageStringEvent) == 0x18);
}
