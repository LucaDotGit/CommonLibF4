#pragma once

#include "RE/H/hkPtrAndInt.hpp"

namespace RE
{
	class __declspec(novtable) hkSlot
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hkSlot;
		inline static constexpr const auto& VTABLE = VTABLE::hkSlot;

		virtual ~hkSlot(); // 0x00

		// add
		virtual auto MatchMethod(const void* a_data, std::int32_t a_size) -> std::uint32_t = 0; // 0x01

		// members
		hkPtrAndInt<hkSlot, std::uint32_t, 3> next; // 0x08
		void* object{nullptr};						// 0x10
	};

	static_assert(sizeof(hkSlot) == 0x18);
}
