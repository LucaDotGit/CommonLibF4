#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class __declspec(novtable) ExtraItemDropper : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraItemDropper;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraItemDropper;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::ItemDropper;

		ExtraItemDropper() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraItemDropper() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		ObjectRefHandle dropperRef; // 0x18
	};

	static_assert(sizeof(ExtraItemDropper) == 0x20);

}
