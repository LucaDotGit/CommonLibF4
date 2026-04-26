#pragma once

namespace RE
{
	class ExperienceMeterDisplayData
	{
	public:
		// members
		std::uint32_t xpAmount;		  // 00
		REX::Float32 progressPercent; // 04
		bool showLevelUp;			  // 08
		bool syncedXP;				  // 09
	};
	static_assert(sizeof(ExperienceMeterDisplayData) == 0x0C);
}
