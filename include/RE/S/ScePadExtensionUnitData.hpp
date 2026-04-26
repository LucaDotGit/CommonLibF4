#pragma once

namespace RE
{
	class ScePadExtensionUnitData
	{
	public:
		// members
		std::uint32_t extensionUnitId;		 // 00
		std::array<std::uint8_t, 1> reserve; // 04
		std::uint8_t dataLength;			 // 05
		std::array<std::uint8_t, 10> data;	 // 06
	};
	static_assert(sizeof(ScePadExtensionUnitData) == 0x10);
}
