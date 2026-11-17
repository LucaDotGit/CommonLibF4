#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraLeveledItem : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraLeveledItem;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraLeveledItem;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::LeveledItem;

		ExtraLeveledItem() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLeveledItem() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		TESFormID levItem{0}; // 0x10
	};

	static_assert(sizeof(ExtraLeveledItem) == 0x20);
}
