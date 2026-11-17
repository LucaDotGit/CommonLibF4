#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraCharge : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraCharge;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraCharge;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Charge;

		ExtraCharge() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraCharge() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		REX::Float32 charge{static_cast<REX::Float32>(0.0)}; // 0x18
	};

	static_assert(sizeof(ExtraCharge) == 0x20);
}
