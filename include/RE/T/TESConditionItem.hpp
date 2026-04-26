#pragma once

#include "RE/C/CONDITION_ITEM_DATA.hpp"
#include "RE/C/ConditionCheckParams.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class TESConditionItem
	{
	public:
		GAME_HEAP_REDEFINE_NEW(TESConditionItem);

		[[nodiscard]] REX::Float32 GetComparisonValue()
		{
			using FuncType = decltype(&TESConditionItem::GetComparisonValue);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESConditionItem::GetComparisonValue };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] bool IsTrue(TESObjectREFR* a_actionRef, TESObjectREFR* a_targetRef)
		{
			using FuncType = bool (*)(TESConditionItem*, TESObjectREFR*, TESObjectREFR*);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESConditionItem::IsTrue01 };
			return std::invoke(FUNC, this, a_actionRef, a_targetRef);
		}

		[[nodiscard]] bool IsTrue(ConditionCheckParams& a_params)
		{
			using FuncType = bool (*)(TESConditionItem*, ConditionCheckParams&);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESConditionItem::IsTrue02 };
			return std::invoke(FUNC, this, a_params);
		}

		// members
		TESConditionItem* next{ nullptr }; // 00
		CONDITION_ITEM_DATA data;		   // 08
	};
	static_assert(sizeof(TESConditionItem) == 0x38);
}
