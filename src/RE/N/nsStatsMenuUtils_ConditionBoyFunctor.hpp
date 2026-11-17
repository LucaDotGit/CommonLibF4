#pragma once

namespace RE::nsStatsMenuUtils
{
	class ConditionBoyFunctor
	{
	public:
		// members
		std::uint32_t bodyFlags; // 0x00
		std::uint32_t headFlags; // 0x04
	};

	static_assert(sizeof(ConditionBoyFunctor) == 0x08);
}
