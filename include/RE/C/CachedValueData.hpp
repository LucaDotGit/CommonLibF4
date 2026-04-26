#pragma once

namespace RE
{
	class CachedValueData
	{
	public:
		// members
		REX::Float32 value; // 00
		bool dirty;			// 04
	};
	static_assert(sizeof(CachedValueData) == 0x08);
}
