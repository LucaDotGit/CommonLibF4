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

		[[nodiscard]]
		auto GetComparisonValue() -> REX::Float32
		{
			using FuncType = decltype(&TESConditionItem::GetComparisonValue);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESConditionItem::GetComparisonValue);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto IsTrue(TESObjectREFR* a_actionRef, TESObjectREFR* a_targetRef) -> bool
		{
			using FuncType = bool (*)(TESConditionItem*, TESObjectREFR*, TESObjectREFR*);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESConditionItem::IsTrue01);
			return std::invoke(FUNC, this, a_actionRef, a_targetRef);
		}

		[[nodiscard]]
		auto IsTrue(ConditionCheckParams& a_params) -> bool
		{
			using FuncType = bool (*)(TESConditionItem*, ConditionCheckParams&);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESConditionItem::IsTrue02);
			return std::invoke(FUNC, this, a_params);
		}

		// members
		TESConditionItem* next{nullptr}; // 0x00
		CONDITION_ITEM_DATA data;		 // 0x08
	};

	static_assert(sizeof(TESConditionItem) == 0x38);
}
