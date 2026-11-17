#pragma once

namespace RE
{
	class XPChangeData
	{
	public:
		// members
		std::uint32_t playerLevel;			  // 0x00
		REX::Float32 initialExperiencePoints; // 0x04
		REX::Float32 experiencePointsAdded;	  // 0x08
		bool syncedXP;						  // 0x0C
	};

	static_assert(sizeof(XPChangeData) == 0x10);
}
