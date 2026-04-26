#pragma once

#include "RE/B/BSExtraData.hpp"

namespace RE
{
	class __declspec(novtable) ExtraStartingWorldOrCell
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraStartingWorldOrCell };
		inline static constexpr auto VTABLE{ VTABLE::ExtraStartingWorldOrCell };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kStartingWorldOrCell };

		ExtraStartingWorldOrCell()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraStartingWorldOrCell() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		TESForm* startingWorldOrCell{ nullptr }; // 18
	};
	static_assert(sizeof(ExtraStartingWorldOrCell) == 0x20);
}
