#include "RE/I/InventoryUserUIUtils.hpp"

namespace RE::InventoryUserUIUtils::Impl
{
	void AddItemCardInfoEntry(
		::Scaleform::GFx::Value& a_array,
		::Scaleform::GFx::Value& a_newEntry,
		const BSFixedStringCS& a_textID,
		::Scaleform::GFx::Value& a_value,
		REX::Float32 a_difference,
		REX::Float32 a_totalDamage,
		REX::Float32 a_compareDamage)
	{
		using FuncType = decltype(&Impl::AddItemCardInfoEntry);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::InventoryUserUIUtils::AddItemCardInfoEntry };
		std::invoke(FUNC, a_array, a_newEntry, a_textID, a_value, a_difference, a_totalDamage, a_compareDamage);
	}
}

namespace RE::InventoryUserUIUtils
{
	void AddItemCardInfoEntry(
		::Scaleform::GFx::Value& a_array,
		::Scaleform::GFx::Value& a_entry,
		const char* a_name,
		::Scaleform::GFx::Value a_value,
		REX::Float32 a_difference,
		REX::Float32 a_totalValue,
		REX::Float32 a_comparisonValue)
	{
		Impl::AddItemCardInfoEntry(a_array, a_entry, a_name, a_value, a_difference, a_totalValue, a_comparisonValue);
	}

	void AddItemCardInfoEntry(
		::Scaleform::GFx::Value& a_array,
		::Scaleform::GFx::Value& a_entry,
		const char* a_name,
		::Scaleform::GFx::Value a_value)
	{
		Impl::AddItemCardInfoEntry(a_array, a_entry, a_name, a_value);
	}

	void AddItemCardInfoEntry(
		::Scaleform::GFx::Value& a_array,
		const char* a_name,
		::Scaleform::GFx::Value a_value)
	{
		auto entry = ::Scaleform::GFx::Value();
		Impl::AddItemCardInfoEntry(a_array, entry, a_name, a_value);
	}
}
