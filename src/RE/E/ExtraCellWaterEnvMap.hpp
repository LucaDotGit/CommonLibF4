#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class TESTexture;

	class __declspec(novtable) ExtraCellWaterEnvMap : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraCellWaterEnvMap;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraCellWaterEnvMap;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::CellWaterEnvMap;

		ExtraCellWaterEnvMap() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCellWaterEnvMap() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		TESTexture* waterEnvMap{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraCellWaterEnvMap) == 0x20);
}
