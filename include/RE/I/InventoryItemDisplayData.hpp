#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/I/InventoryUserUIInterfaceEntry.hpp"
#include "Scaleform/G/GFx_Value.hpp"

namespace RE
{
	class InventoryItemDisplayData
	{
	public:
		InventoryItemDisplayData() = default;

		InventoryItemDisplayData(const ObjectRefHandle a_inventoryRef, const InventoryUserUIInterfaceEntry& a_entry)
		{
			using FuncType = void (InventoryItemDisplayData::*)(const ObjectRefHandle, const InventoryUserUIInterfaceEntry&);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::InventoryItemDisplayData::ctor };
			FUNC(this, a_inventoryRef, a_entry);
		}

		void PopulateFlashObject(::Scaleform::GFx::Value& a_flashObject) const
		{
			a_flashObject.SetMember("text", ::Scaleform::GFx::Value(itemName.data()));
			a_flashObject.SetMember("count", ::Scaleform::GFx::Value(itemCount));
			a_flashObject.SetMember("equipState", ::Scaleform::GFx::Value(equipState));
			a_flashObject.SetMember("filterFlag", ::Scaleform::GFx::Value(filterFlag));
			a_flashObject.SetMember("isLegendary", ::Scaleform::GFx::Value(isLegendary));
			a_flashObject.SetMember("favorite", ::Scaleform::GFx::Value(isFavorite));
			a_flashObject.SetMember("taggedForSearch", ::Scaleform::GFx::Value(isTaggedForSearch));
			a_flashObject.SetMember("isBetterThanEquippedItem", ::Scaleform::GFx::Value(isBetterThanEquippedItem));
		}

		// members
		BSFixedStringCS itemName;				// 00
		std::uint32_t itemCount{ 0 };			// 08
		std::uint32_t equipState{ 0 };			// 0C
		std::uint32_t filterFlag{ 0 };			// 10
		bool isLegendary{ false };				// 14
		bool isFavorite{ false };				// 15
		bool isTaggedForSearch{ false };		// 16
		bool isBetterThanEquippedItem{ false }; // 17
	};
	static_assert(sizeof(InventoryItemDisplayData) == 0x18);
}
