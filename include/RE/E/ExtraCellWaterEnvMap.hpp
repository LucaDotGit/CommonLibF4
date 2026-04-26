#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class TESTexture;

	class __declspec(novtable) ExtraCellWaterEnvMap
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraCellWaterEnvMap };
		inline static constexpr auto VTABLE{ VTABLE::ExtraCellWaterEnvMap };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kCellWaterEnvMap };

		ExtraCellWaterEnvMap()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCellWaterEnvMap() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		TESTexture* waterEnvMap{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraCellWaterEnvMap) == 0x20);
}
