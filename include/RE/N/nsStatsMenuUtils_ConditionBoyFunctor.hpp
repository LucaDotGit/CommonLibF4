#pragma once

namespace RE::nsStatsMenuUtils
{
	class ConditionBoyFunctor
	{
	public:
		// members
		std::uint32_t bodyFlags; // 00
		std::uint32_t headFlags; // 04
	};
	static_assert(sizeof(ConditionBoyFunctor) == 0x08);
}
