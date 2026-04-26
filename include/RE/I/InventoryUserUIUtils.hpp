#pragma once

#include "RE/B/BSFixedString.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace RE::InventoryUserUIUtils::Impl
{
	void AddItemCardInfoEntry(
		::Scaleform::GFx::Value& a_array,
		::Scaleform::GFx::Value& a_newEntry,
		const BSFixedStringCS& a_textID,
		::Scaleform::GFx::Value& a_value,
		REX::Float32 a_difference = 0.0_f32,
		REX::Float32 a_totalDamage = std::numeric_limits<REX::Float32>::max(),
		REX::Float32 a_compareDamage = std::numeric_limits<REX::Float32>::max());
}

namespace RE::InventoryUserUIUtils
{
	void AddItemCardInfoEntry(
		::Scaleform::GFx::Value& a_array,
		::Scaleform::GFx::Value& a_entry,
		const char* a_name,
		::Scaleform::GFx::Value a_value,
		REX::Float32 a_difference,
		REX::Float32 a_totalValue = std::numeric_limits<REX::Float32>::max(),
		REX::Float32 a_comparisonValue = std::numeric_limits<REX::Float32>::max());
	void AddItemCardInfoEntry(
		::Scaleform::GFx::Value& a_array,
		::Scaleform::GFx::Value& a_entry,
		const char* a_name = "",
		::Scaleform::GFx::Value a_value = ::Scaleform::GFx::Value(0));
	void AddItemCardInfoEntry(
		::Scaleform::GFx::Value& a_array,
		const char* a_name,
		::Scaleform::GFx::Value a_value);
}
