#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraHealth : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraHealth;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraHealth;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Health;

		ExtraHealth() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraHealth() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		REX::Float32 health{static_cast<REX::Float32>(0.0)}; // 0x18
	};

	static_assert(sizeof(ExtraHealth) == 0x20);
}
