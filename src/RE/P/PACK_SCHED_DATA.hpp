#pragma once

namespace RE
{
	class PACK_SCHED_DATA
	{
	public:
		// members
		std::int8_t month;	   // 0x00
		std::int8_t dayOfWeek; // 0x01
		std::int8_t date;	   // 0x02
		std::int8_t hour;	   // 0x03
		std::int8_t min;	   // 0x04
		std::int32_t duration; // 0x08
	};

	static_assert(sizeof(PACK_SCHED_DATA) == 0x0C);
}
