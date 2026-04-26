#pragma once

namespace RE
{
	class XPChangeData
	{
	public:
		// members
		std::uint32_t playerLevel;			  // 00
		REX::Float32 initialExperiencePoints; // 04
		REX::Float32 experiencePointsAdded;	  // 08
		bool syncedXP;						  // 0C
	};
	static_assert(sizeof(XPChangeData) == 0x10);
}
