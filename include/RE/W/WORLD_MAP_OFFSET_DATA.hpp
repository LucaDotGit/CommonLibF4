#pragma once

namespace RE
{
	class WORLD_MAP_OFFSET_DATA
	{
	public:
		// members
		REX::Float32 mapScale;	 // 00
		REX::Float32 mapOffsetX; // 04
		REX::Float32 mapOffsetY; // 08
		REX::Float32 mapOffsetZ; // 0C
	};
	static_assert(sizeof(WORLD_MAP_OFFSET_DATA) == 0x10);
}
