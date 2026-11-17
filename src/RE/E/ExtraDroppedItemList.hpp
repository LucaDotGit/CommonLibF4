#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"

namespace RE
{
	class __declspec(novtable) ExtraDroppedItemList : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraDroppedItemList;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraDroppedItemList;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::DroppedItemList;

		ExtraDroppedItemList() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraDroppedItemList() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		BSSimpleList<ObjectRefHandle> droppedItemList; // 0x10
	};

	static_assert(sizeof(ExtraDroppedItemList) == 0x28);
}
