#pragma once

namespace RE
{
	class WORLD_MAP_DATA
	{
	public:
		// members
		std::uint32_t usableWidth;	// 0x00
		std::uint32_t usableHeight; // 0x04
		std::int16_t nwCellX;		// 0x08
		std::int16_t nwCellY;		// 0x0A
		std::int16_t seCellX;		// 0x0C
		std::int16_t seCellY;		// 0x0E
	};

	static_assert(sizeof(WORLD_MAP_DATA) == 0x10);
}
