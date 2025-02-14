#pragma once

#include "RE/NetImmerse/NiExtraData.hpp"

namespace RE
{
	class NiBooleanExtraData : public NiExtraData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiBooleanExtraData };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::NiBooleanExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiBooleanExtraData };

		bool data; // 18
	};
	static_assert(sizeof(NiBooleanExtraData) == 0x20);
}
