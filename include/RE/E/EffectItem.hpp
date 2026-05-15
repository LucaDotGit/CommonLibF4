#pragma once

#include "RE/B/BSStringT.hpp"
#include "RE/E/EffectItemData.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/T/TESCondition.hpp"

namespace RE
{
	class EffectItem
	{
	public:
		GAME_HEAP_REDEFINE_NEW(EffectItem);

		void GetDescription(BSString* a_buffer, const char* a_beginTagFormat, const char* a_endTagFormat, REX::Float32 a_magnitude, REX::Float32 a_duration)
		{
			using FuncType = decltype(&EffectItem::GetDescription);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::EffectItem::GetDescription };
			std::invoke(FUNC, this, a_buffer, a_beginTagFormat, a_endTagFormat, a_magnitude, a_duration);
		}

		// members
		EffectItemData data;		  // 00
		EffectSetting* effectSetting; // 10
		REX::Float32 rawCost;		  // 18
		TESCondition conditions;	  // 20
	};
	static_assert(sizeof(EffectItem) == 0x28);
}
