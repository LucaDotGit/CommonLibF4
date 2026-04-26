#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCellWaterType
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraCellWaterType };
		inline static constexpr auto VTABLE{ VTABLE::ExtraCellWaterType };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kCellWaterType };

		ExtraCellWaterType()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCellWaterType() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		TESWaterForm* waterType{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraCellWaterType) == 0x20);
}
