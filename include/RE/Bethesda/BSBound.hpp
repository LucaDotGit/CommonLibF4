#pragma once

#include "RE/NetImmerse/NiExtraData.hpp"
#include "RE/NetImmerse/NiPoint.hpp"

namespace RE
{
	class __declspec(novtable) BSBound
		: public NiExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSBound };
		inline static constexpr auto VTABLE{ VTABLE::BSBound };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::BSBound };

		// members
		NiPoint3 center;  // 18
		NiPoint3 extents; // 24
	};
	static_assert(sizeof(BSBound) == 0x30);
}
