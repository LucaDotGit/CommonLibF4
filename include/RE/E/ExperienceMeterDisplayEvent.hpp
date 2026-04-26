#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/E/ExperienceMeterDisplayData.hpp"

namespace RE
{
	class ExperienceMeterDisplayEvent
		: public BSTValueEvent<ExperienceMeterDisplayData> // 00
	{
	public:
	};
	static_assert(sizeof(ExperienceMeterDisplayEvent) == 0x10);
}
