#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::PowerUtils
{
	class PowerGrid;
}

namespace RE::Workshop
{
	class DeletedItemInfo;

	class __declspec(novtable) ExtraData : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::Workshop__ExtraData;
		inline static constexpr const auto& VTABLE = VTABLE::Workshop__ExtraData;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Workshop;

		ExtraData() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraData() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		PowerUtils::PowerGrid* currentPowerGrid;	// 0x18
		BSTArray<PowerUtils::PowerGrid*> powerGrid; // 0x20
		BSTArray<DeletedItemInfo*> deletedItems;	// 0x38
		std::int32_t powerRating;					// 0x50
		bool offGridItems;							// 0x54
	};

	static_assert(sizeof(ExtraData) == 0x58);
}
