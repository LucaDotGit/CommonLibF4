#include "RE/N/nsStatsMenuUtils.hpp"

namespace RE::nsStatsMenuUtils
{
	void GetEffectDisplayInfo(MagicItem* a_item, EffectItem* a_effect, REX::Float32& a_magnitude, REX::Float32& a_duration)
	{
		using FuncType = decltype(&nsStatsMenuUtils::GetEffectDisplayInfo);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::nsStatsMenuUtils::GetEffectDisplayInfo };
		std::invoke(FUNC, a_item, a_effect, a_magnitude, a_duration);
	}
}
