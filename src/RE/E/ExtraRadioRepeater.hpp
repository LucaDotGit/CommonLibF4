#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class __declspec(novtable) ExtraRadioRepeater : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraRadioRepeater;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraRadioRepeater;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::RadioRepeater;

		ExtraRadioRepeater() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraRadioRepeater() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		ObjectRefHandle transmitterToRepeat;					  // 0x18
		REX::Float32 innerRadius{static_cast<REX::Float32>(0.0)}; // 0x1C
		REX::Float32 outerRadius{static_cast<REX::Float32>(0.0)}; // 0x20
		bool unlimitedRange{false};								  // 0x24
	};

	static_assert(sizeof(ExtraRadioRepeater) == 0x28);
}
