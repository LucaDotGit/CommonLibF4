#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSPointerHandle.hpp"

namespace RE
{
	class __declspec(novtable) ExtraAshPileRef
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraAshPileRef };
		inline static constexpr auto VTABLE{ VTABLE::ExtraAshPileRef };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kAshPileRef };

		ExtraAshPileRef()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraAshPileRef() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		ObjectRefHandle ashPileRef; // 18
	};
	static_assert(sizeof(ExtraAshPileRef) == 0x20);

}
