#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/E/ExtraLightDataStruct.hpp"

namespace RE
{
	class __declspec(novtable) ExtraLightData : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraLightData;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraLightData;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::LightData;

		ExtraLightData() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraLightData() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		ExtraLightDataStruct data; // 0x18
	};

	static_assert(sizeof(ExtraLightData) == 0x30);

}
