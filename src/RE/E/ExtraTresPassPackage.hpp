#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/T/TrespassPackage.hpp"

namespace RE
{
	class __declspec(novtable) ExtraTresPassPackage : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraTresPassPackage;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraTresPassPackage;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::TresPassPackage;

		ExtraTresPassPackage() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraTresPassPackage() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		TrespassPackage* package{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraTresPassPackage) == 0x20);
}
