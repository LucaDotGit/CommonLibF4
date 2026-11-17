#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class __declspec(novtable) ExtraAshPileRef : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraAshPileRef;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraAshPileRef;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::AshPileRef;

		ExtraAshPileRef() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraAshPileRef() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		ObjectRefHandle ashPileRef; // 0x18
	};

	static_assert(sizeof(ExtraAshPileRef) == 0x20);

}
