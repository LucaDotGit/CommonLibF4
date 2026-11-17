#pragma once

namespace RE
{
	class ExperienceMeterDisplayData
	{
	public:
		// members
		std::uint32_t xpAmount;		  // 0x00
		REX::Float32 progressPercent; // 0x04
		bool showLevelUp;			  // 0x08
		bool syncedXP;				  // 0x09
	};

	static_assert(sizeof(ExperienceMeterDisplayData) == 0x0C);
}
