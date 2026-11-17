#pragma once

namespace RE
{
	class EffectItemData
	{
	public:
		// members
		REX::Float32 magnitude; // 0x00
		std::int32_t area;		// 0x04
		std::int32_t duration;	// 0x08
	};

	static_assert(sizeof(EffectItemData) == 0x0C);
}
