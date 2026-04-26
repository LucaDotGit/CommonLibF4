#pragma once

#include "RE/B/BSTSmartPointer.hpp"
#include "RE/P/PipboyInventoryData.hpp"

namespace RE
{
	enum class EffectIconColor : std::int32_t;

	class PlayerActiveEffectData
	{
	public:
		// members
		BSTSmartPointer<ActiveEffect> effect;								 // 00
		REX::Enum<PipboyInventoryData::ITEM_ICON_ID, std::int32_t> effectID; // 08
		REX::Enum<EffectIconColor, std::int32_t> color;						 // 0C
	};
	static_assert(sizeof(PlayerActiveEffectData) == 0x10);
}
