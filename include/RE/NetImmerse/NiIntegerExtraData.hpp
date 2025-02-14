#pragma once

#include "RE/NetImmerse/NiExtraData.hpp"

namespace RE
{
	class NiIntegerExtraData : public NiExtraData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiIntegerExtraData };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::NiIntegerExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiIntegerExtraData };

		std::int32_t data; // 18
	};
	static_assert(sizeof(NiIntegerExtraData) == 0x20);
}
