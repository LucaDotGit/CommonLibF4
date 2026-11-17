#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraStartingWorldOrCell : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraStartingWorldOrCell;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraStartingWorldOrCell;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::StartingWorldOrCell;

		ExtraStartingWorldOrCell() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraStartingWorldOrCell() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		TESForm* startingWorldOrCell{nullptr}; // 0x18
	};

	static_assert(sizeof(ExtraStartingWorldOrCell) == 0x20);
}
