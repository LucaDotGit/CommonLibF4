#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCellSkyRegion : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraCellSkyRegion;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraCellSkyRegion;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::CellSkyRegion;

		ExtraCellSkyRegion() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCellSkyRegion() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		TESRegion* region{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraCellSkyRegion) == 0x20);
}
