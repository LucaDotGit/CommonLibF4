#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCellWaterType : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraCellWaterType;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraCellWaterType;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::CellWaterType;

		ExtraCellWaterType() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCellWaterType() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		TESWaterForm* waterType{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraCellWaterType) == 0x20);
}
