#pragma once

namespace RE
{
	class EffectItemData
	{
	public:
		// members
		REX::Float32 magnitude; // 00
		std::int32_t area;		// 04
		std::int32_t duration;	// 08
	};
	static_assert(sizeof(EffectItemData) == 0x0C);
}
