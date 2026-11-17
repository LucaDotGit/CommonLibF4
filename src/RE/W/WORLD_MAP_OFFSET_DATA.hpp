#pragma once

namespace RE
{
	class WORLD_MAP_OFFSET_DATA
	{
	public:
		// members
		REX::Float32 mapScale;	 // 0x00
		REX::Float32 mapOffsetX; // 0x04
		REX::Float32 mapOffsetY; // 0x08
		REX::Float32 mapOffsetZ; // 0x0C
	};

	static_assert(sizeof(WORLD_MAP_OFFSET_DATA) == 0x10);
}
