#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class __declspec(novtable) ExtraItemDropper
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraItemDropper };
		inline static constexpr auto VTABLE{ VTABLE::ExtraItemDropper };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kItemDropper };

		ExtraItemDropper()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraItemDropper() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		ObjectRefHandle dropperRef; // 18
	};
	static_assert(sizeof(ExtraItemDropper) == 0x20);

}
