#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCellImageSpace
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraCellImageSpace };
		inline static constexpr auto VTABLE{ VTABLE::ExtraCellImageSpace };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kCellImageSpace };

		ExtraCellImageSpace()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCellImageSpace() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		TESImageSpace* imageSpace{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraCellImageSpace) == 0x20);

}
