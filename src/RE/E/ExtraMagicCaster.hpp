#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/M/MagicCaster.hpp"

namespace RE
{
	class __declspec(novtable) ExtraMagicCaster : public BSExtraData // 0x00
	{
	public:
		static constexpr const auto& RTTI = RTTI::ExtraMagicCaster;
		static constexpr const auto& VTABLE = VTABLE::ExtraMagicCaster;
		static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::MagicCaster;

		ExtraMagicCaster() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraMagicCaster() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		MagicCaster magicCaster; // 0x18
	};

	static_assert(sizeof(ExtraMagicCaster) == 0x60);
}
