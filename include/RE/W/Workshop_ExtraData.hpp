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

	class __declspec(novtable) ExtraData
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::Workshop__ExtraData };
		inline static constexpr auto VTABLE{ VTABLE::Workshop__ExtraData };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kWorkshop };

		ExtraData()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraData() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		PowerUtils::PowerGrid* currentPowerGrid;	// 18
		BSTArray<PowerUtils::PowerGrid*> powerGrid; // 20
		BSTArray<DeletedItemInfo*> deletedItems;	// 38
		std::int32_t powerRating;					// 50
		bool offGridItems;							// 54
	};
	static_assert(sizeof(ExtraData) == 0x58);
}
