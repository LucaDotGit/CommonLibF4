#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/R/RADIO_DATA.hpp"

namespace RE
{
	class __declspec(novtable) ExtraRadioData
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraRadioData };
		inline static constexpr auto VTABLE{ VTABLE::ExtraRadioData };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kRadioData };

		ExtraRadioData()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraRadioData() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		RADIO_DATA data; // 18
	};
	static_assert(sizeof(ExtraRadioData) == 0x28);
}
