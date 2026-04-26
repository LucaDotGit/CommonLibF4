#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraLeveledItem
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraLeveledItem };
		inline static constexpr auto VTABLE{ VTABLE::ExtraLeveledItem };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kLeveledItem };

		ExtraLeveledItem()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLeveledItem() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		TESFormID levItem{ 0 }; // 10
	};
	static_assert(sizeof(ExtraLeveledItem) == 0x20);
}
