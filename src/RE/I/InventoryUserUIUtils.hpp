#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace RE
{
	class BGSInventoryItem;
}

namespace RE::InventoryUserUIUtils
{
	void AddItemCardInfoEntry(
		Scaleform::GFx::Value& a_array,
		Scaleform::GFx::Value& a_entry,
		const char* a_name,
		Scaleform::GFx::Value a_value,
		REX::Float32 a_difference,
		REX::Float32 a_totalValue = std::numeric_limits<REX::Float32>::max(),
		REX::Float32 a_comparisonValue = std::numeric_limits<REX::Float32>::max());

	void AddItemCardInfoEntry(
		Scaleform::GFx::Value& a_array,
		Scaleform::GFx::Value& a_entry,
		const char* a_name = "",
		Scaleform::GFx::Value a_value = Scaleform::GFx::Value(0));

	void AddItemCardInfoEntry(Scaleform::GFx::Value& a_array, const char* a_name, Scaleform::GFx::Value a_value);

	void PopulateItemCardInfo_Helper(
		Scaleform::GFx::Value& a_target,
		const BGSInventoryItem& a_item,
		std::uint32_t a_stackID,
		const BSScrapArray<BSTTuple<const BGSInventoryItem*, std::uint32_t>>& a_compareItems,
		bool a_compareArmorWeightAndValue);
}
