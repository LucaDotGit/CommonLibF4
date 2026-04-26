#pragma once

namespace RE
{
	class PACK_SCHED_DATA
	{
	public:
		// members
		std::int8_t month;	   // 00
		std::int8_t dayOfWeek; // 01
		std::int8_t date;	   // 02
		std::int8_t hour;	   // 03
		std::int8_t min;	   // 04
		std::int32_t duration; // 08
	};
	static_assert(sizeof(PACK_SCHED_DATA) == 0x0C);
}
