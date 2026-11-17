#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/R/RADIO_DATA.hpp"

namespace RE
{
	class __declspec(novtable) ExtraRadioData : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraRadioData;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraRadioData;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::RadioData;

		ExtraRadioData() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraRadioData() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		RADIO_DATA data; // 0x18
	};

	static_assert(sizeof(ExtraRadioData) == 0x28);
}
