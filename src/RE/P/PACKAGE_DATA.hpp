#pragma once

namespace RE
{
	class PACKAGE_DATA
	{
	public:
		// members
		std::uint32_t packFlags;			// 0x00
		std::int8_t packType;				// 0x04
		std::int8_t interruptOverrideType;	// 0x05
		std::int8_t maxSpeed;				// 0x06
		std::uint16_t foBehaviorFlags;		// 0x08
		std::uint16_t packageSpecificFlags; // 0x0A
	};

	static_assert(sizeof(PACKAGE_DATA) == 0x0C);
}
