#pragma once

namespace RE
{
	class PACKAGE_DATA
	{
	public:
		// members
		std::uint32_t packFlags;			// 00
		std::int8_t packType;				// 04
		std::int8_t interruptOverrideType;	// 05
		std::int8_t maxSpeed;				// 06
		std::uint16_t foBehaviorFlags;		// 08
		std::uint16_t packageSpecificFlags; // 0A
	};
	static_assert(sizeof(PACKAGE_DATA) == 0x0C);
}
