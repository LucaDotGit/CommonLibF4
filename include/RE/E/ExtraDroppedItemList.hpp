#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"

namespace RE
{
	class __declspec(novtable) ExtraDroppedItemList
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraDroppedItemList };
		inline static constexpr auto VTABLE{ VTABLE::ExtraDroppedItemList };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kDroppedItemList };

		ExtraDroppedItemList()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraDroppedItemList() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		BSSimpleList<ObjectRefHandle> droppedItemList; // 10
	};
	static_assert(sizeof(ExtraDroppedItemList) == 0x28);
}
