#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraAmmo : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraAmmo;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraAmmo;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Ammo;

		ExtraAmmo() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraAmmo() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		std::uint32_t count{0}; // 0x18
	};

	static_assert(sizeof(ExtraAmmo) == 0x20);
}
