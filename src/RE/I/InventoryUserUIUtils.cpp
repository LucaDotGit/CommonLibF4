#include "RE/I/InventoryUserUIUtils.hpp"

#include "RE/B/BSFixedString.hpp"

namespace RE::InventoryUserUIUtils::Impl
{
	namespace
	{
		void AddItemCardInfoEntry(
			Scaleform::GFx::Value& a_array,
			Scaleform::GFx::Value& a_newEntry,
			const BSFixedStringCS& a_textID,
			Scaleform::GFx::Value& a_value,
			REX::Float32 a_difference = static_cast<REX::Float32>(0.0),
			REX::Float32 a_totalDamage = std::numeric_limits<REX::Float32>::max(),
			REX::Float32 a_compareDamage = std::numeric_limits<REX::Float32>::max())
		{
			using FuncType = decltype(&Impl::AddItemCardInfoEntry);
			static const auto FUNC = REL::Relocation<FuncType>(ID::InventoryUserUIUtils::AddItemCardInfoEntry);
			std::invoke(FUNC, a_array, a_newEntry, a_textID, a_value, a_difference, a_totalDamage, a_compareDamage);
		}
	}
}

namespace RE::InventoryUserUIUtils
{
	void AddItemCardInfoEntry(
		Scaleform::GFx::Value& a_array,
		Scaleform::GFx::Value& a_entry,
		const char* a_name,
		Scaleform::GFx::Value a_value,
		REX::Float32 a_difference,
		REX::Float32 a_totalValue,
		REX::Float32 a_comparisonValue)
	{
		Impl::AddItemCardInfoEntry(a_array, a_entry, a_name, a_value, a_difference, a_totalValue, a_comparisonValue);
	}

	void AddItemCardInfoEntry(
		Scaleform::GFx::Value& a_array,
		Scaleform::GFx::Value& a_entry,
		const char* a_name,
		Scaleform::GFx::Value a_value)
	{
		Impl::AddItemCardInfoEntry(a_array, a_entry, a_name, a_value);
	}

	void AddItemCardInfoEntry(Scaleform::GFx::Value& a_array, const char* a_name, Scaleform::GFx::Value a_value)
	{
		auto entry = Scaleform::GFx::Value();
		Impl::AddItemCardInfoEntry(a_array, entry, a_name, a_value);
	}

	void PopulateItemCardInfo_Helper(
		Scaleform::GFx::Value& a_target,
		const BGSInventoryItem& a_item,
		std::uint32_t a_stackID,
		const BSScrapArray<BSTTuple<const BGSInventoryItem*, std::uint32_t>>& a_compareItems,
		bool a_compareArmorWeightAndValue)
	{
		using FuncType = decltype(&PopulateItemCardInfo_Helper);
		static const auto FUNC = REL::Relocation<FuncType>(ID::InventoryUserUIUtils::PopulateItemCardInfo_Helper);
		std::invoke(FUNC, a_target, a_item, a_stackID, a_compareItems, a_compareArmorWeightAndValue);
	}
}
