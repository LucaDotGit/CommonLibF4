#pragma once

#include "RE/NetImmerse/NiExtraData.hpp"

namespace RE
{
	class NiFloatExtraData : public NiExtraData
	{
	public:
		static constexpr auto RTTI{ RTTI::NiFloatExtraData };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiFloatExtraData };
		static constexpr auto VTABLE{ VTABLE::NiFloatExtraData };

		float data; // 18
	};
	static_assert(sizeof(NiFloatExtraData) == 0x20);
}
