#pragma once

#include "RE/NetImmerse/NiExtraData.hpp"

namespace RE
{
	class NiStringExtraData
		: public NiExtraData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiStringExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiStringExtraData };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::NiStringExtraData };

		// members
		BSFixedString data; // 18
	};
	static_assert(sizeof(NiStringExtraData) == 0x20);
}
