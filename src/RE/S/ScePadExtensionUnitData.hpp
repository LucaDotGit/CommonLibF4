#pragma once

namespace RE
{
	class ScePadExtensionUnitData
	{
	public:
		// members
		std::uint32_t extensionUnitId;		 // 0x00
		std::array<std::uint8_t, 1> reserve; // 0x04
		std::uint8_t dataLength;			 // 0x05
		std::array<std::uint8_t, 10> data;	 // 0x06
	};

	static_assert(sizeof(ScePadExtensionUnitData) == 0x10);
}
