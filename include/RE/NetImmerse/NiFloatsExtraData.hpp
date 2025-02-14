#pragma once

#include "RE/NetImmerse/NiExtraData.hpp"

namespace RE
{
	class NiFloatsExtraData : public NiExtraData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiFloatsExtraData };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::NiFloatsExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiFloatsExtraData };

		std::uint32_t size;	 // 18
		std::uint32_t pad1C; // 1C
		float* data;		 // 20
	};
	static_assert(sizeof(NiFloatsExtraData) == 0x28);
}
