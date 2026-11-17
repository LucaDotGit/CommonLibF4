#pragma once

namespace RE
{
	class CachedValueData
	{
	public:
		// members
		REX::Float32 value; // 0x00
		bool dirty;			// 0x04
	};

	static_assert(sizeof(CachedValueData) == 0x08);
}
