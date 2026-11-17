#pragma once

namespace Scaleform
{
	enum StatBasicValues : std::int32_t
	{
		StatGroup_Default = 0,
		StatGroup_Core = 16,

		Stat_Mem = StatGroup_Default + 1,
		Stat_Default_Mem = Stat_Mem + 1,

		StatHeap_Start = StatGroup_Core,

		Stat_MaxId = 64 << 6,
		Stat_EntryCount = 512,

		HeapId_Default = 1
	};
}
