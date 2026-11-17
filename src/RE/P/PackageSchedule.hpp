#pragma once

#include "RE/P/PACK_SCHED_DATA.hpp"

namespace RE
{
	class PackageSchedule
	{
	public:
		// members
		PACK_SCHED_DATA psData; // 0x00
	};

	static_assert(sizeof(PackageSchedule) == 0x0C);
}
