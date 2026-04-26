#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCellSkyRegion
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraCellSkyRegion };
		inline static constexpr auto VTABLE{ VTABLE::ExtraCellSkyRegion };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kCellSkyRegion };

		ExtraCellSkyRegion()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCellSkyRegion() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		TESRegion* region{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraCellSkyRegion) == 0x20);
}
