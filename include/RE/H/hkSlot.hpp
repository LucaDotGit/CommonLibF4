#pragma once

#include "RE/H/hkPtrAndInt.hpp"

namespace RE
{
	class __declspec(novtable) hkSlot
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkSlot };
		inline static constexpr auto VTABLE{ VTABLE::hkSlot };

		virtual ~hkSlot(); // 00

		// add
		virtual std::uint32_t MatchMethod(const void* a_data, std::int32_t a_size) = 0; // 01

		// members
		hkPtrAndInt<hkSlot, std::uint32_t, 3> next; // 08
		void* object{ nullptr };					// 10
	};
	static_assert(sizeof(hkSlot) == 0x18);
}
