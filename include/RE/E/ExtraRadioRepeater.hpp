#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class __declspec(novtable) ExtraRadioRepeater
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraRadioRepeater };
		inline static constexpr auto VTABLE{ VTABLE::ExtraRadioRepeater };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kRadioRepeater };

		ExtraRadioRepeater()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraRadioRepeater() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		ObjectRefHandle transmitterToRepeat; // 18
		REX::Float32 innerRadius{ 0.0_f32 }; // 1C
		REX::Float32 outerRadius{ 0.0_f32 }; // 20
		bool unlimitedRange{ false };		 // 24
	};
	static_assert(sizeof(ExtraRadioRepeater) == 0x28);
}
