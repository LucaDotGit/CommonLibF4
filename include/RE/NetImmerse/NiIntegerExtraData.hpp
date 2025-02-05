#pragma once

#include "RE/NetImmerse/NiExtraData.hpp"

namespace RE
{
	class NiIntegerExtraData : public NiExtraData
	{
	public:
		static constexpr auto RTTI{ RTTI::NiIntegerExtraData };
		static constexpr auto Ni_RTTI{ Ni_RTTI::NiIntegerExtraData };
		static constexpr auto VTABLE{ VTABLE::NiIntegerExtraData };

		std::int32_t data; // 18
	};
	static_assert(sizeof(NiIntegerExtraData) == 0x20);
}
