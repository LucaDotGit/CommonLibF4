#pragma once

#include "RE/NetImmerse/NiExtraData.hpp"

namespace RE
{
	class NiStringsExtraData : public NiExtraData
	{
	public:
		inline static constexpr auto RTTI{ RTTI::NiStringsExtraData };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::NiStringsExtraData };
		inline static constexpr auto VTABLE{ VTABLE::NiStringsExtraData };

		std::uint32_t size;	 // 18
		std::uint32_t pad1C; // 1C
		char** data;		 // 20
	};
	static_assert(sizeof(NiStringsExtraData) == 0x28);
}
