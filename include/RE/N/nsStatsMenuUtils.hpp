#pragma once

namespace RE
{
	class EffectItem;
}

namespace RE::nsStatsMenuUtils
{
	void GetEffectDisplayInfo(MagicItem* a_item, EffectItem* a_effect, REX::Float32& a_magnitude, REX::Float32& a_duration);
}
